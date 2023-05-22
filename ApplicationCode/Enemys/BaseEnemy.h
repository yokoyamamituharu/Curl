#pragma once
#include<DirectXMath.h>
#include"Sprite.h"
class BaseEnemy
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	virtual ~BaseEnemy() {};

	XMFLOAT2 Getpos() { return pos; }

	void SetMoveAddLength(float moveAddLength_) { this->moveAddLength = moveAddLength_; }
	float GetMoveAddLength() { return moveAddLength; }

	void SetMoveLength(float moveLength_) { this->moveLength = moveLength_; }
	float GetMoveLength() { return moveLength; }

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }
	bool GetBloodHitFlag() { return bloodHitFlag; }

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }
	bool GetTowerHitFlag() { return towerHitFlag; }

	virtual	void Update() = 0;

	void Create();
	void Create(int type);
	

	virtual void Draw() = 0;
private:
	Sprite* sprite{};
	XMFLOAT2 pos{};

	float angle{};
	float moveLength{};
	float moveAddLength = 1;

	bool bloodHitFlag{};
	bool towerHitFlag{};
	bool dead{};
};

