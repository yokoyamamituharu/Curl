#pragma once
#include<DirectXMath.h>

#include"Sprite.h"
class BaseEnemy
{
private:
protected:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

	enum EnemyType
	{
		vampire = 7,//ŒÂ‘Ì
		basilisk,//‰t‘Ì
		rabbit,//‹C‘Ì
	};
	enum BloodState {
		NONE_1,
		solid_1,
		liquid_1,
		gas_1
	};
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

	void SetGetBloodType(int getBloodType_) { this->getBloodType = getBloodType_; }
	bool GetGetBloodType() { return getBloodType; }



	virtual	void Update() = 0;

	
	//void Create(int type);
	

	virtual void Draw() = 0;
protected:
	Sprite* sprite{};
	XMFLOAT2 pos{};

	float angle{};
	float moveLength{};
	float moveAddLength = 1;

	int getBloodType{};
	int hitBloodType{};
	int anBloodType{};

	bool bloodHitFlag{};
	bool towerHitFlag{};
	bool dead{};
};

