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

	void Update();

	void Shot();

	void Draw(ScrollCamera* scroll);

	void AddPlayerVector(Vector2 vec);

	float GetSpeed() { return speed_; }

	Sprite* GetSprite() { return sprites_[state_]; }

	void SetCamera(ScrollCamera* camera) { this->camera_ = camera; }
private:
	std::map<int, Sprite*> sprites_;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;
	XMFLOAT2 position_{};
	float heat_ = 0;
	int maxHeatDiray_ = 15;
	int heatDiray_ = maxHeatDiray_;
	int state_ = (int)State::none;
	KeyInputHandler* handler = nullptr;
	float speed_ = 2.0f;
	ScrollCamera* camera_ = nullptr;
};