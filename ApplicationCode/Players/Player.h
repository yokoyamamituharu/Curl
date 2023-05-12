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

private:
	Sprite* sprite_ = nullptr;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;
};