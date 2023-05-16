#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include<memory>
#include<list>
using namespace std;

class Enemy
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;



public:
	enum EnemyType
	{
		individual = 7,//ŒÂ‘Ì
		liquid,//‰t‘Ì
		gas,//‹C‘Ì
	};
	enum BloodState {
		NONE_1,
		solid_1,
		liquid_1,
		gas_1
	};
	Enemy();
	~Enemy();

	static Enemy* Create(int tipe);
	static Enemy* Create();

	static unique_ptr<Enemy> UniqueCreate(int tipe);
	static unique_ptr<Enemy> UniqueCreate();

	void Update();

	void Draw();

	XMFLOAT2 Getpos() { return pos; }

	bool GetBloodHitFlag() { return bloodHitFlag; }
	bool GetTowerHitFlag() { return towerHitFlag; }

	void SetMoveAddLength(int moveAddLength_) { this->moveAddLength = moveAddLength_; }
	int GetMoveAddLength() { return moveAddLength; }

	void SetMoveLength(int moveLength_) { this->moveLength = moveLength_; }
	int GetMoveLength() { return moveLength; }

	void SetBloodType(int bloodTipe_) { this->bloodType = bloodTipe_; }
	int GetBloodType() { return bloodType; }

	void SetHitBloodType(int hitBloodType_) { this->hitBloodType = hitBloodType_; }
	int GetHitBloodType() { return hitBloodType; }

	void SetAnBloodType(int anBloodType_) { this->anBloodType = anBloodType_; }
	int GetAnBloodType() { return anBloodType; }

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }

	XMFLOAT2 GerEnemyPos() { return pos; }

protected:
	Sprite* sprite{};
	XMFLOAT2 pos{};
	int enemyType{};
	int bloodType{};
	int hitBloodType{};
	int anBloodType{};
	float angle{};
	float moveLength{};
	float moveAddLength = 1;

	bool bloodHitFlag{};
	bool towerHitFlag{};
};