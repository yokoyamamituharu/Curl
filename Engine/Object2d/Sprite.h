#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <memory>
#include "ScrollCamera.h"
#include "Camera2D.h"

class Sprite
{
public: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //サブクラス

    // 頂点データ
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData {
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat;   // ３Ｄ変換行列
	};

public: //静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static bool StaticInitialize(ID3D12Device* device, int32_t window_width, int32_t window_height);
	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texnumber">テクスチャ番号</param>
	/// <param name="filename">画像ファイル名</param>
	/// <returns></returns>
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);
	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト1</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();
	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="anchorpoint">アンカーポイント</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	/// <returns></returns>
	static Sprite* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	/// <summary>
	/// スプライト生成(unique_ptr)
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="anchorpoint"><アンカーポイント/param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	/// <returns></returns>
	static std::unique_ptr<Sprite> UniquePtrCreate(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	static void SetCamera(ScrollCamera* camera) { camera_ = camera; }
	static void SetCamera2D(Camera2D* camera) { camera2D = camera; }

protected: //静的メンバ変数
	//テクスチャの最大枚数
	static const int32_t srvCount = 512;
	//頂点数
	static const int32_t vertNum = 4;
	//デバイス
	static ID3D12Device* device;
	//デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	//コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	//射影行列
	static XMMATRIX matProjection;
	//デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[srvCount];
	//カメラ
	static ScrollCamera* camera_;
	static Camera2D* camera2D;
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="anchorpoint">アンカーポイント</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	/// <summary>
	/// 位置取得
	/// </summary>
	/// <returns>位置</returns>
	const XMFLOAT2& GetPosition() { return position; }
	/// <summary>
	/// 大きさ取得
	/// </summary>
	/// <returns>大きさ</returns>
	const XMFLOAT2& GetSize() { return size; }
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Initialize();
	/// <summary>
	/// 角度の設定
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(float rotation);
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT2 position);
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(XMFLOAT2 size);
	/// <summary>
	/// アンカーポイントの設定
	/// </summary>
	/// <param name="anchorpoint"></param>
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	/// <summary>
	/// 左右反転の設定
	/// </summary>
	/// <param name="isFlipX">左右反転</param>
	void SetIsFlipX(bool isFlipX);
	/// <summary>
	/// 上下反転の設定
	/// </summary>
	/// <param name="isFlipY">上下反転</param>
	void SetIsFlipY(bool isFlipY);
	/// <summary>
	/// スプライト色の設定
	/// </summary>
	/// <param name="color">スプライト色</param>
	void SetColor(XMFLOAT3 color) {
		this->color.x = color.x;
		this->color.y = color.y;
		this->color.z = color.z;
	}
	/// <summary>
	/// アルファ値の設定
	/// </summary>
	/// <param name="alpha"></param>
	void SetAlpha(float alpha) { this->alpha = alpha; }
	/// <summary>
	/// 画像左の補正設定
	/// </summary>
	/// <param name="isLeftSizeCorrection"></param>
	void SetLeftSizeCorrection(bool isLeftSizeCorrection) { this->isLeftSizeCorrection = isLeftSizeCorrection; }
	/// <summary>
	/// 画像右の補正設定
	/// </summary>
	/// <param name="isRightSizeCorrection"></param>
	void SetRightSizeCorrection(bool isRightSizeCorrection) { this->isRightSizeCorrection = isRightSizeCorrection; }
	/// <summary>
	/// テクスチャ範囲設定
	/// </summary>
	/// <param name="texBase">テクスチャ左上座標</param>
	/// <param name="texSize">テクスチャサイズ</param>
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	/// <summary>
	/// UIにする
	/// </summary>
	/// <param name="isUi"></param>
	void SetUi(bool isUi) { this->isUi = isUi; }
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();	

protected: //メンバ変数
	//頂点バッファ;
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//定数バッファ;
	ComPtr<ID3D12Resource> constBuff;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position = {};
	// ワールド行列
	XMMATRIX matWorld;
	// 色(RGBA)
	XMFLOAT4 color = { 1, 1, 1, 1 };
	//アルファ値
	float alpha = 1.0f;
	// テクスチャ番号
	UINT texNumber = 0;
	// 大きさ
	XMFLOAT2 size = { 100, 100 };
	//左サイズ補正フラグ
	bool isLeftSizeCorrection = true;
	//右サイズ補正フラグ
	bool isRightSizeCorrection = true;
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0.5f, 0.5f };
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// テクスチャ左上座標
	XMFLOAT2 texBase = { 0, 0 };
	// テクスチャサイズ
	XMFLOAT2 texSize = { 100, 100 };
	bool isUi = false;	
private: //メンバ関数
	/// <summary>
	/// 頂点データ転送
	/// </summary>
	void TransferVertices();
};

