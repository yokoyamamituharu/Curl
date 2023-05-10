#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include<memory>
#include<list>

using namespace std;

class Enemys
{
private://è»ó™

	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;
	/*template <class T> using unique_ptr = std::unique_ptr<T>;
	template <class T> using list = std::list<T>;*/
	//template <class T> using make_unique = std::make_unique<T>;
private:
	struct Enemy
	{
		Sprite* sprite{};
		XMFLOAT2 pos{};
		int enemyType{};
		bool bloodHitFlag{};
		int bloodType{};
		float angle{};
		float moveLength{};
		~Enemy();

	};

	enum EnemyType
	{
		individual,//å¬ëÃ
		liquid,//âtëÃ
		gas,//ãCëÃ
	};


public:

	void Initialize();

	void Update();

	void Draw();

	void Delete();

	~Enemys();

private:
	Sprite* sprite{};
	XMFLOAT2 pos{};
	int enemyType{};
	bool bloodHitFlag{};
	int bloodType{};
	float angle{};
	float moveLength{};
	//Enemy* enemys_[36]{};
	RandCreate* randCreate_{};
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	list<unique_ptr<Enemy>> enemys3_{};
};

