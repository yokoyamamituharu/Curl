#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include<memory>
#include<list>
#include"Enemy.h"

using namespace std;

class Enemys:public Enemy
{
private://È—ª

	
private:

public:
	enum EnemyType
	{
		individual = 7,//ŒÂ‘Ì
		liquid,//‰t‘Ì
		gas,//‹C‘Ì
	};

	Enemys();
	~Enemys();

	static Enemys* Create();

	void Update(int32_t towerHp,int playerHp);

	void Draw();

	void EnemyCreate();

	void EnemyDelete();

	list<unique_ptr<Enemy>> Get() { return std::move(enemys3_); }
	

protected:
	//Enemy* enemys_[36]{};
	int enemyNumber_{};
	int enemyCreateTime{};
	RandCreate* randCreate_{};
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	list<unique_ptr<Enemy>> enemys3_{};
};

