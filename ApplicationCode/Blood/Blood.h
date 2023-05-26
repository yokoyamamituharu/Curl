#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
class Blood
{
public:
	enum class Temperature
	{
		NONE,
		solid,
		liquid,
		gas
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

	static std::unique_ptr<Blood> UniquePtrCreate(DirectX::XMFLOAT2 position, Temperature state, DirectX::XMFLOAT2 goal,DirectX::XMFLOAT2* playerPos);

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();
	/// <summary>
	/// ‰·“x‚ğã¸‚³‚¹‚é
	/// </summary>
	void Rising();
	/// <summary>
	/// ‰·“x‚ğŒ¸­‚³‚¹‚é
	/// </summary>
	void Decrease();
	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw();
	/// <summary>
	/// €–S”»’è‚ğæ“¾
	/// </summary>
	/// <returns>€–S”»’è</returns>
	bool GetDead();
	/// <summary>
	/// €–S”»’è‚É‚·‚é
	/// </summary>
	void SetDead();
	/// <summary>
	/// Œ»İ‚Ìó‘Ô‚ğæ“¾
	/// </summary>
	/// <returns>ó‘Ô</returns>
	int GetTemperature() { return temp_; }
	/// <summary>
	/// ˆÊ’u‚ğæ“¾
	/// </summary>
	/// <returns>ˆÊ’u</returns>
	DirectX::XMFLOAT2 GetPosition() { return position_; }
	/// <summary>
	/// 
	/// </summary>
	void SetState(State state) { state_ = (int)state; }

	int GetState() { return state_; }

	DirectX::XMFLOAT2  GetPos() { return position_; }

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
	DirectX::XMFLOAT2 position_{};
	DirectX::XMFLOAT2 goal_{};
	DirectX::XMVECTOR oldvec_{};
	DirectX::XMFLOAT2* playerPos_{};
	const float speed_ = 30.0f;
	int maxTempDray = 20;
	int tempDray = 0;
};