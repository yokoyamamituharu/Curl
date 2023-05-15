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

	Enemy();
	~Enemy();

	static Enemy* Create(int tipe);

	static unique_ptr<Enemy> UniqueCreate(int tipe);
	static unique_ptr<Enemy> UniqueCreate();

	void Update();

	void Draw();

	XMFLOAT2 Getpos() { return pos; }

	bool GetBloodHitFlag() { return bloodHitFlag; }
	bool GetTowerHitFlag() { return towerHitFlag; }

	void SetBloadTipe(int bloodTipe_) { this->bloodType = bloodTipe_; }

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }

	XMFLOAT2 GerEnemyPos() { return pos; }

protected:
	Sprite* sprite{};
	XMFLOAT2 pos{};
	int enemyType{};
	int bloodType{};
	float angle{};
	float moveLength{};

	bool bloodHitFlag{};
	bool towerHitFlag{};
};