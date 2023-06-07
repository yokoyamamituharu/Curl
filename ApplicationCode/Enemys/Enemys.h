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

	void EnemyCreate(const int phase);

	void EnemyHitBlood();


	void EnemyHitTower();

	bool GetGameFlag() { return gameFlag; }

	list<unique_ptr<VampireEnemy>>& GetVampires() { return Vampires_; }
	list<unique_ptr<BasiliskEnemy>>& GetBasiliskes() { return Basiliskes_; }
	list<unique_ptr<RabbitEnemy>>& GetRabbits() { return Rabbits_; }
	//void SetEnemys(list<unique_ptr<Enemy>> enemys) { this->enemys3_ = move(enemys); };
	void Draw();

protected:
	
	int enemyNumber_{};//�o�����Ă���G�̑���
	int enemyCreateTime{};//��������
	RandCreate* randCreate_{};//�����_��
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	
	list<unique_ptr<VampireEnemy>> Vampires_{};
	list<unique_ptr<BasiliskEnemy>> Basiliskes_{};
	list<unique_ptr<RabbitEnemy>> Rabbits_{};

	int deadCount = 0;
	bool gameFlag = 0;

};

