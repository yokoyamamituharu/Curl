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
	int GetPlayerHp() { return playerHp_; }
	void SetPlayerHp(int playerHp) { this->playerHp_ = playerHp; }

	std::list<std::unique_ptr<Blood>>& GetBloods() { return bloods_;}
	void SetBlood(std::list<std::unique_ptr<Blood>> blood) { this->bloods_ = std::move(blood); }
protected:
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;
};