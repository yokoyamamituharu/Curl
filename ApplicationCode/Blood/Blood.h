#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
#include "Vector2.h"

class Blood
{
public:
	enum class Temperature
	{
		NONE,
		solid,
		liquid,
		gas,
		droppedLiquid
	};

	enum class State {
		none,
		idle,
		shot,
		back,
		heat
	};

	Blood() = default;

	~Blood();

	static Blood* Create(DirectX::XMFLOAT2 position, Temperature state);

	static std::unique_ptr<Blood> UniquePtrCreate(Vector2 position, Temperature state, Vector2 targetPos_, Vector2* playerPos);

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
	int GetTemperature() { return temp_; }
	/// <summary>
	/// 位置を取得
	/// </summary>
	/// <returns>位置</returns>
	DirectX::XMFLOAT2 GetPosition() { return position_; }
	/// <summary>
	/// 
	/// </summary>
	void SetState(State state) { state_ = (int)state; }

	int GetState() { return state_; }

	Vector2  GetPos() { return position_; }

	void HeatWaveOnCollision();
	void ColdWaveOnCollision();
private:

public:

private:
	std::map<int, Sprite*> sprites_;
	int temp_ = (int)Temperature::NONE;
	int state_ = (int)State::none;
	int deadTimer_ = 100;
	bool isDead = false;
	Vector2 position_{};
	Vector2 targetPos_{};
	Vector2 oldvec_{};
	Vector2* playerPos_{};
	const float initSpeed_ = 5.0f;
	float speed_ = 8.0f;
	int maxTempDray = 20;
	int tempDray = 0;
};