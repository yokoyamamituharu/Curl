#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include<memory>
#include<list>
#include"Enemy.h"

using namespace std;

class Enemys
{
private://�ȗ�

	
private:

public:
	enum EnemyType
	{
		individual = 7,//��
		liquid,//�t��
		gas,//�C��
	};

	Enemys();
	~Enemys();

	static Enemys* Create();

	void Update(int32_t towerHp,int playerHp);

	void EnemyCreate();

	void EnemyHitBlood();

	void EnemyHitTower();

	list<unique_ptr<Enemy>>& GetEnemys() { return enemys3_; }
	void SetEnemys(list<unique_ptr<Enemy>> enemys) { this->enemys3_ = move(enemys); };
	void Draw();

protected:
	//Enemy* enemys_[36]{};
	int enemyNumber_{};
	int enemyCreateTime{};
	RandCreate* randCreate_{};
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	list<unique_ptr<Enemy>> enemys3_{};
};

