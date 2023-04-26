﻿#include "FbxLoader.h"

const std::string FbxLoader::baseDirectory = "Engine/Resources/";
const std::string FbxLoader::defaultTextureFileName = "Images/white1x1.png";
const std::string FbxLoader::modelFolder = "3DModels/fbx/";
using namespace DirectX;

FbxLoader* FbxLoader::GetInstance()
{
	static FbxLoader instance;
	return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device) {
	//nullチェック
	assert(fbxManager == nullptr);
	//引数からメンバ変数に代入
	this->device = device;
	//FBXマネージャの生成
	fbxManager = FbxManager::Create();
	//FBXマネージャの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	//FBXインポータの生成
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize() {
	//各種FBXインスタンスの破棄
	fbxImporter->Destroy();
	fbxManager->Destroy();
}

FBXModel* FbxLoader::LoadModelFromFile(const string& modelName) {
	//モデルと同じ名前のフォルダから読み込む
	const string directoryPath = baseDirectory + modelFolder + modelName + "/";
	//拡張子
	const string fileName = modelName + ".fbx";
	//連結する
	const string fullPath = directoryPath + fileName;

	//ファイル名を指定してFBXファイルを読み込む
	if (!fbxImporter->Initialize(fullPath.c_str(), -1, fbxManager->GetIOSettings())) {
		assert(0);
	}

	//シーン生成
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

	//ファイルからロードしたFBXの情報をシーンにインポート
	fbxImporter->Import(fbxScene);

	//ポリゴンを三角面化
	FbxGeometryConverter geometryConverter(fbxManager);
	geometryConverter.Triangulate(fbxScene, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(fbxScene);

	//モデル生成
	FBXModel* model = new FBXModel();
	model->name = modelName;

	//FBXノードの数を取得
	int32_t nodeCount = fbxScene->GetNodeCount();

	//あらかじめ必要数分のメモリを確保
	model->nodes.reserve(nodeCount);

	//ルートノードから順に解析してモデルに流し込む
	ParseNodeRecursive(model, fbxScene->GetRootNode());

	//FBXシーン解放
	model->fbxScene = fbxScene;

	//バッファ生成
	model->CreateBuffers(device);

	return model;
}

void FbxLoader::ParseNodeRecursive(FBXModel* model, FbxNode* fbxNode, Node* parent) {
	//ノード名を取得
	string name = fbxNode->GetName();

	//モデルにノードを追加
	model->nodes.emplace_back();
	Node& node = model->nodes.back();

	//FBXノードの情報を解析してノードに記録
	node.name = fbxNode->GetName();

	//FBXノードのローカル移動情報
	FbxDouble3 rotation = fbxNode->LclRotation.Get();
	FbxDouble3 scaling = fbxNode->LclScaling.Get();
	FbxDouble3 translation = fbxNode->LclTranslation.Get();

	//形式変換して代入
	node.rotation = { (float)rotation[0], (float)rotation[1], (float)rotation[2], 0.0f };
	node.scaling = { (float)scaling[0], (float)scaling[1], (float)scaling[2], 0.0f };
	node.translation = { (float)translation[0], (float)translation[1], (float)translation[2], 1.0f };

	//回転角をDegree(度)からラジアンに変換
	node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
	node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
	node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);

	//スケール、回転、平行移動行列の計算
	XMMATRIX matScaling, matRotation, matTranslation;
	matScaling = XMMatrixScalingFromVector(node.scaling);
	matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
	matTranslation = XMMatrixTranslationFromVector(node.translation);

	//ローカル変形行列の計算
	node.transform = XMMatrixIdentity();
	node.transform *= matScaling;
	node.transform *= matRotation;
	node.transform *= matTranslation;

	//グローバル変形行列の計算
	node.globalTransform = node.transform;
	if (parent) {
		node.parent = parent;
		//親の変形を乗算
		node.globalTransform *= parent->globalTransform;
	}

	//FBXノードのメッシュ情報を解析
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			model->meshNode = &node;
			ParseMesh(model, fbxNode);
		}
	}

	//子ノードに対して再帰呼び出し
	for (int32_t i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
	}
}

void FbxLoader::ParseMesh(FBXModel* model, FbxNode* fbxNode) {
	//ノードのメッシュを取得
	FbxMesh* fbxMesh = fbxNode->GetMesh();

	//面を構成するデータの読み取り
	ParseMeshFaces(model, fbxMesh);
	//マテリアルの読み取り
	ParseMaterial(model, fbxNode);
	//スキニング情報の読み取り
	ParseSkin(model, fbxMesh);
}

void FbxLoader::ParseMeshFaces(FBXModel* model, FbxMesh* fbxMesh)
{
	auto& vertices = model->vertices;
	auto& indices = model->indices;

	//1ファイルに複数メッシュのモデルは非対応
	assert(indices.size() == 0);

	//面の数
	const int32_t polygonCount = fbxMesh->GetPolygonCount();

	//UVデータの数
	const int32_t textureUVCount = fbxMesh->GetTextureUVCount();

	//UV名リスト
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//頂点データ配列を確保
	FBXModel::VertexPosNormalUvSkin vert{};
	model->vertices.resize(polygonCount * 3, vert);

	//FBXメッシュの頂点座標配列を取得
	FbxVector4* pCoord = fbxMesh->GetControlPoints();
	int32_t indexCount = 0;
	controlPoints.clear();
	controlPoints.resize(fbxMesh->GetControlPointsCount());

	//面ごとの情報読み取り
	for (int32_t i = 0; i < polygonCount; i++) {
		//面を構成する頂点の数を取得 (3なら三角ポリゴン)
		const int32_t polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 3);

		//1頂点ずつ処理
		for (int32_t j = 0; j < polygonSize; j++) {
			int32_t index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);

			controlPoints[index].push_back(indexCount);

			//頂点法線読み込み
			FBXModel::VertexPosNormalUvSkin& vertex = vertices[indexCount];
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal)) {
				vertex.normal.x = (float)normal[0];
				vertex.normal.y = (float)normal[1];
				vertex.normal.z = (float)normal[2];
			}
			//頂点座標読み込み
			vertex.pos.x = (float)pCoord[index][0];
			vertex.pos.y = (float)pCoord[index][1];
			vertex.pos.z = (float)pCoord[index][2];

			//テクスチャUV読み込み
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0番決め打ちで読み込み
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv.x = (float)uvs[0];
					vertex.uv.y = (float)uvs[1] * -1.0f;
				}
			}

			//インデックス配列に頂点インデックス追加
			//3頂点目までなら
			if (j < 3) {
				//1点追加し、他の2点と三角形を構築する
				indices.push_back(indexCount);
			}
			//4頂点目
			else {
				//3点追加し、
				//四角形の0,1,2,3の内 2,3,0で三角形を構築する
				int32_t index2 = indices[indices.size() - 1];
				int32_t index3 = index;
				int32_t index0 = indices[indices.size() - 3];
				indices.push_back(index2);
				indices.push_back(index3);
				indices.push_back(index0);
			}
			indexCount++;
		}
	}
}

void FbxLoader::ParseMaterial(FBXModel* model, FbxNode* fbxNode)
{
	const int32_t materialCount = fbxNode->GetMaterialCount();
	if (materialCount > 0) {
		//先頭のマテリアルを取得
		FbxSurfaceMaterial* material = fbxNode->GetMaterial(0);
		//テクスチャを読み込んだかどうかを表すフラグ
		bool textureLoaded = false;

		if (material) {
			//FBXSurfaceLambertクラスか判定
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
				FbxSurfaceLambert* lambert = static_cast<FbxSurfaceLambert*>(material);

				//環境光係数
				FbxPropertyT<FbxDouble3> ambient = lambert->Ambient;
				model->ambient.x = (float)ambient.Get()[0];
				model->ambient.y = (float)ambient.Get()[1];
				model->ambient.z = (float)ambient.Get()[2];

				//拡散反射光係数
				FbxPropertyT<FbxDouble3> diffuse = lambert->Diffuse;
				model->diffuse.x = (float)diffuse.Get()[0];
				model->diffuse.y = (float)diffuse.Get()[1];
				model->diffuse.z = (float)diffuse.Get()[2];

				//ディフューズテクスチャを取り出す
				const FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
				if (diffuseProperty.IsValid()) {
					const FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>();
					if (texture) {
						const char* filepath = texture->GetFileName();
						//ファイルパスからファイル名抽出
						string path_str(filepath);
						string name = ExtractFileName(path_str);
						//テクスチャ読み込み
						LoadTexture(model, baseDirectory + modelFolder + model->name + "/" + name);
						textureLoaded = true;
					}
				}
			}
		}
		//テクスチャがない場合は白テクスチャを張る
		if (!textureLoaded) {
			LoadTexture(model, baseDirectory + defaultTextureFileName);
		}
	}
}

void FbxLoader::LoadTexture(FBXModel* model, const std::string& fullPath)
{
	HRESULT result = S_FALSE;
	//WICテクスチャのロード
	TexMetadata& metadata = model->metadata;
	ScratchImage& scratchImg = model->scratchImg;
	//ユニコード文字列に変換
	wchar_t wfilepath[128];
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilepath, _countof(wfilepath));
	result = LoadFromWICFile(wfilepath, WIC_FLAGS_NONE, &metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}
}

std::string FbxLoader::ExtractFileName(const std::string& path) {
	size_t pos1;
	//区切り文字 '\\' が出てくる一番最後の部分を検索
	pos1 = path.rfind('\\');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	//区切り文字 '/' が出てくる一番最後の部分を検索
	pos1 = path.rfind('/');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	return path;
}

void FbxLoader::ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src)
{
	for (int32_t i = 0; i < 4; i++) {
		for (int32_t j = 0; j < 4; j++) {
			dst->r[i].m128_f32[j] = (float)src.Get(i, j);
		}
	}
}

void FbxLoader::ParseSkin(FBXModel* model, FbxMesh* fbxMesh) {
	//スキニング情報
	FbxSkin* fbxSkin = static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));

	//スキニング情報がなければ終了
	if (fbxSkin == nullptr) {
		//各頂点についての処理
		for (int32_t i = 0; i < model->vertices.size(); i++) {
			//最初のボーンの影響を100%にすることでボーンなしに対応
			model->vertices[i].boneIndex[0] = 0;
			model->vertices[i].boneWeight[0] = 1.0f;
		}

		return;
	}

	//ボーン配列の参照
	std::vector<FBXModel::Bone>& bones = model->bones;

	//ボーンの数
	int32_t clusterCount = fbxSkin->GetClusterCount();
	bones.reserve(clusterCount);

	//全てのボーンについて
	for (int32_t i = 0; i < clusterCount; i++) {
		//FBXボーン情報
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);

		//ボーン自体のノードの名前を取得
		const char* boneName = fbxCluster->GetLink()->GetName();

		//新しくボーンを追加し、追加したボーンの参照を得る
		bones.emplace_back(FBXModel::Bone(boneName));
		FBXModel::Bone& bone = bones.back();

		//自作ボーンとFBXボーンを紐づける
		bone.fbxCluster = fbxCluster;

		//FBXから初期姿勢行列を取得する
		FbxAMatrix fbxMat;
		fbxCluster->GetTransformLinkMatrix(fbxMat);

		//XMMATRIX型に変換する
		XMMATRIX initialPose;
		ConvertMatrixFromFbx(&initialPose, fbxMat);

		//初期姿勢行列の逆行列を得る
		bone.invInitialPose = XMMatrixInverse(nullptr, initialPose);
	}

	struct WeightSet {
		UINT index;
		float weight;
	};

	//二次元配列(ジャグ配列)
	//list:頂点が影響を受けるボーンの全リスト
	//vector:それを全頂点分
	std::vector<std::list<WeightSet>>weightLists(controlPoints.size());

	//全てのボーンについて
	for (int32_t i = 0; i < clusterCount; i++) {
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
		//このボーンに影響を受ける頂点の数
		int32_t controlPointIndicesCount = fbxCluster->GetControlPointIndicesCount();
		//このボーンに影響を受ける頂点の配列
		int32_t* controlPointIndices = fbxCluster->GetControlPointIndices();
		double* controlPointWeights = fbxCluster->GetControlPointWeights();

		//影響を受ける全頂点について
		for (int32_t j = 0; j < controlPointIndicesCount; j++) {
			//頂点番号
			int32_t vertIndex = controlPointIndices[j];
			//スキンウェイト
			float weight = (float)controlPointWeights[j];
			//その頂点の影響を受けるボーンリストに、ボーンとウェイトのペアを追加
			weightLists[vertIndex].emplace_back(WeightSet{ (UINT)i, weight });
		}
	}

	//頂点配列書き換え用の参照
	auto& vertices = model->vertices;
	//各頂点について処理
	for (int32_t i = 0; i < controlPoints.size(); i++) {
		//頂点のウェイトから最も大きい4つを選択
		auto& weightList = weightLists[i];
		//大小比較用のラムダ式を指定して降順にソート
		weightList.sort(
			[](auto const& lhs, auto const& rhs) {
				//左の要素の方が大きければtrue そうでなければfalse
				return lhs.weight > rhs.weight;
			});
		if (weightList.size() > 4) {
			weightList.resize(4);
		}

		for (int32_t j = 0; j < controlPoints[i].size(); j++) {
			int32_t weightArrayIndex = 0;
			//降順ソート済みのウェイトリストから
			for (auto& weightSet : weightList) {
				std::vector<int32_t>& controlPoint = controlPoints[i];
				int32_t indexCount = controlPoint[j];
				//頂点データに書き込み
				vertices[indexCount].boneIndex[weightArrayIndex] = weightSet.index;
				vertices[indexCount].boneWeight[weightArrayIndex] = weightSet.weight;
				//4つに達したら終了
				if (++weightArrayIndex >= FBXModel::MAX_BONE_INDICES) {
					float weight = 0.0f;
					//2番目以降のウェイトを合計
					for (int32_t k = 1; k < FBXModel::MAX_BONE_INDICES; k++) {
						weight += vertices[indexCount].boneWeight[k];
					}
					//合計で1.0f(100%)になるように調整
					vertices[indexCount].boneWeight[0] = 1.0f - weight;
					break;
				}
			}
		}
	}
}