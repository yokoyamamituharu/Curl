#pragma once
#include "Sprite.h"
#include "Blood.h"
#include "list"
#include "Vector2.h"
#include "ScrollCamera.h"

class KeyInputHandler;
class Player
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	enum class State
	{
		none,
		idle,
		heat
	};

	Player();

	~Player();

	static Player* Create();

	static Player* Create(Vector2 pos, float rote, int hp, int maxBlood);

	void Update(ScrollCamera* camera);

	void Shot(ScrollCamera* camera);

	void Draw(ScrollCamera* scroll);

	void AddPlayerVector(Vector2 vec);

	void Move(ScrollCamera* camera);

	float GetSpeed() { return speed_; }

	Sprite* GetSprite() { return sprites_[state_]; }

	int GetPlayerHp() { return playerHp_; }
	void SetPlayerHp(int playerHp) { this->playerHp_ = playerHp; }
	std::list<std::unique_ptr<Blood>>& GetBloods() { return bloods_; }
	int GetBloodGauge() { return bloodGauge_; }
	int GetMaxBloodGauge() { return maxBlood_; }

	void SetBlood(std::list<std::unique_ptr<Blood>> blood) { this->bloods_ = std::move(blood); }
private:
	std::map<int, Sprite*> sprites_;
	Vector2 position_{};
	float heat_ = 0;
	int maxHeatDiray_ = 0;
	int heatDiray_ = maxHeatDiray_;
	int state_ = (int)State::none;
	KeyInputHandler* handler_ = nullptr;
	float speed_ = 4.0f;
	int playerHp_ = 10;
	int maxBlood_ = 0;
	int bloodGauge_ = 0;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;

	Sprite* heatWave_ = nullptr;
	Sprite* coldWave_ = nullptr;

	bool isHeatWave = false;
	float heatExtend = 0;
	float heatAlpha = 1;

	bool isColdWave = false;
	float coldExtend = 0;
	float coldAlpha = 1;
};