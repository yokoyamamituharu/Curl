#pragma once
#include <DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include <memory>
#include <list>

#include "VampireEnemy.h"
#include "BasiliskEnemy.h"
#include "RabbitEnemy.h"
#include "Vector2.h"
#include <sstream>

using namespace std;

class EnemyManager
{
private:

public: //構造体

	enum class EnemyType {
		Vampire,
		Rabbit,
		Basilisk
	};

	struct EnemySpawnData {
		Vector2 spawnPoint_; //出現場所
		EnemyType enemyType_; //敵タイプ
		int32_t waitTime_; //出現待機時間
	};

public:
	enum EnemyType
	{
		individual = 7,//個体
		liquid,//液体
		gas,//気体
	};

	EnemyManager();
	~EnemyManager();

	static EnemyManager* Create();

	void Update(int32_t towerHp,int playerHp,Vector2 camera);

	void EnemyCreate(const int phase);

	void EnemyHitBlood();

	void EnemyHitTower();

	void EnemysDead();

	bool GetGameFlag() { return gameFlag; }

	list<unique_ptr<VampireEnemy>>& GetVampires() { return Vampires_; }
	list<unique_ptr<BasiliskEnemy>>& GetBasiliskes() { return Basiliskes_; }
	list<unique_ptr<RabbitEnemy>>& GetRabbits() { return Rabbits_; }

	void EnemySpawnDataLoad();
	void EnemySpawnDataUpdate();
	//void SetEnemys(list<unique_ptr<Enemy>> enemys) { this->enemys3_ = move(enemys); };
	void Draw();

private:
	
	int enemyNumber_{};//出現している敵の送料
	int enemyCreateTime{};//生成時間
	RandCreate* randCreate_{};//ランダム
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	
	list<unique_ptr<VampireEnemy>> Vampires_{};
	list<unique_ptr<BasiliskEnemy>> Basiliskes_{};
	list<unique_ptr<RabbitEnemy>> Rabbits_{};

	list<EnemySpawnData> enemySpawnData_; //敵出現データ
	int32_t waitTimer_ = 500; //出現待機タイマー
	std::stringstream enemySpawnFileData_; //敵出現データ格納用文字列
	std::list<EnemySpawnData>::iterator it_; //イテレータ

	int deadCount = 0;
	bool gameFlag = 0;

};

