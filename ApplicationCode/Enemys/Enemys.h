#pragma once
#include<DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"

class Enemys
{
private://�ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;
	
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
	};

	enum EnemyType
	{
		individual,//��
		liquid,//�t��
		gas,//�C��
	};


public:

	void Initialize();

	void Update();

	void Draw();

	

private:
	Enemy* enemys_[36]{};
	RandCreate* randCreate{};
	KeyInput* keyInput{};
};

