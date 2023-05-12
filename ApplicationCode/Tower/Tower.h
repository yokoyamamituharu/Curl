#pragma once
#include "Sprite.h"
#include "Vector2.h"

class Tower
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tower() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tower() = default;

public: //メンバ関数
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="hp">初期HP</param>
	void Initialize(int32_t hp);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// HP取得
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHP() { return hp_; }

	/// <summary>
	/// タワーオブジェクト取得
	/// </summary>
	/// <returns>タワーオブジェクト</returns>
	Sprite* GetTower() { return tower_.get(); }

private: //メンバ変数
	//HP
	int32_t hp_;
	//座標
	Vector2 pos_;
	//タワーオブジェクト
	std::unique_ptr<Sprite> tower_;

};

