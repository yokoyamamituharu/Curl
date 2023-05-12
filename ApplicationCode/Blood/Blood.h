#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
class Blood
{
public:
	enum STATE {
		NONE,
		solid,
		liquid,
		gas
	};

	Blood() = default;

	~Blood();

	static Blood* Create(DirectX::XMFLOAT2 position, STATE state);

	static std::unique_ptr<Blood> UniquePtrCreate(DirectX::XMFLOAT2 position, STATE state, DirectX::XMFLOAT2 goal);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 温度を上昇させる
	/// </summary>
	void Rising();
	/// <summary>
	/// 温度を減少させる
	/// </summary>
	void Decrease();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 死亡判定を取得
	/// </summary>
	/// <returns>死亡判定</returns>
	bool GetDead();
	/// <summary>
	/// 死亡判定にする
	/// </summary>
	void SetDead();
	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>状態</returns>
	int GetTemperature() { return state_; }
	/// <summary>
	/// 位置を取得
	/// </summary>
	/// <returns>位置</returns>
	DirectX::XMFLOAT2 GetPosition() { return position_; }

private:

public:

private:
	std::map<int, Sprite*> sprites_;
	int state_ = NONE;
	int deadTimer = 100;
	bool isDead = false;
	DirectX::XMFLOAT2 position_{};
	DirectX::XMFLOAT2 goal_{};
	DirectX::XMVECTOR oldvec{};

	const float speed_ = 10.0f;
};