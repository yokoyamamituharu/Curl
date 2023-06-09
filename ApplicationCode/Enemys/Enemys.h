#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include<memory>
#include<list>

#include"VampireEnemy.h"
#include"BasiliskEnemy.h"
#include"RabbitEnemy.h"

using namespace std;

class Enemys
{
private://省略

	
private:

public:
	enum EnemyType
	{
		individual = 7,//個体
		liquid,//液体
		gas,//気体
	};

	Enemys();
	~Enemys();

	static Enemys* Create();

	void Update(int32_t towerHp,int playerHp);

	void EnemyCreate(const int phase);

	void EnemyHitBlood();

	void EnemyHitTower();

	void EnemysDead();

	bool GetGameFlag() { return gameFlag; }

	list<unique_ptr<VampireEnemy>>& GetVampires() { return Vampires_; }
	list<unique_ptr<BasiliskEnemy>>& GetBasiliskes() { return Basiliskes_; }
	list<unique_ptr<RabbitEnemy>>& GetRabbits() { return Rabbits_; }
	//void SetEnemys(list<unique_ptr<Enemy>> enemys) { this->enemys3_ = move(enemys); };
	void Draw();

protected:
	
	int enemyNumber_{};//出現している敵の送料
	int enemyCreateTime{};//生成時間
	RandCreate* randCreate_{};//ランダム
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	
	list<unique_ptr<VampireEnemy>> Vampires_{};
	list<unique_ptr<BasiliskEnemy>> Basiliskes_{};
	list<unique_ptr<RabbitEnemy>> Rabbits_{};

	int deadCount = 0;
	bool gameFlag = 0;

};

