#pragma once
#include "Sprite.h"
#include "Blood.h"
#include "list"

class Player 
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	Player();
	
	~Player();

	static Player* Create();

	void Update();

	void Shot();

	void Draw();

	int GetPlayerHp() { return playerHp_; }
	void SetPlayerHp(int playerHp) { this->playerHp_ = playerHp; }

	std::list<std::unique_ptr<Blood>>& GetBloods() { return bloods_;}
	void SetBlood(std::list<std::unique_ptr<Blood>> blood) { this->bloods_ = std::move(blood); }
protected:
	Sprite* sprite_ = nullptr;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;
	int playerHp_{};
};