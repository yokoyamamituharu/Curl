#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
private: //エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public: //サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		XMMATRIX mat;	// ３Ｄ変換行列
	};

public: //静的メンバ関数
	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int32_t window_width, int32_t window_height);

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// ワールド行列の更新
	/// </summary>
	static void UpdateWorldMatrix();

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// 上方ベクトルのセット
	/// </summary>
	/// <param name="up">上方ベクトル</param>
	static void SetUp(XMFLOAT3 up);

	/// <summary>
	/// ワールド行列のセット
	/// </summary>
	/// <param name="matWorld">ワールド行列</param>
	static void SetMatWorld(XMMATRIX matWorld);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveVector(XMFLOAT3 move);
	static void CameraMoveEyeVector(XMFLOAT3 move);
	static void CameraMoveTargetVector(XMFLOAT3 move);

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	static const XMMATRIX& GetMatView() { return matView; }

	/// <summary>
	/// 射影行列の取得
	/// </summary>
	/// <returns>射影行列</returns>
	static const XMMATRIX& GetMatProjection() { return matProjection; }

	/// <summary>
	/// ビルボード行列を掛ける
	/// </summary>
	/// <returns>ビルボード行列</returns>
	static const XMMATRIX& GetMatBillboard() { return matBillboard; }

	/// <summary>
	/// Y軸ビルボード行列を掛ける
	/// </summary>
	/// <returns>Y軸ビルボード行列</returns>
	static const XMMATRIX& GetMatBillboardY() { return matBillboardY; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	static const XMMATRIX& GetMatWorld() { return matWorld; }

	/// <summary>
	/// ビューポート行列の取得
	/// </summary>
	/// <returns>ビューポート行列</returns>
	static const XMMATRIX& GetMatViewPort() { return matViewPort; }

private: //静的メンバ変数
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	//ワールド行列
	static XMMATRIX matWorld;
	//ビルボード行列
	static XMMATRIX matBillboard;
	//Y軸ビルボード行列
	static XMMATRIX matBillboardY;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	//ビューポート行列
	static XMMATRIX matViewPort;
	//ワールド行列設定のフラグ
	static bool isMatWorldCalc;
};

