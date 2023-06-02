#include"Enemy.h"
#include "SafeDelete.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	delete sprite;

}

Enemy* Enemy::Create(int tipe)
{
	Enemy* enemy = new Enemy();
	
	enemy->enemyType = tipe;
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);
	if (enemy->enemyType == vampire)
	{
		enemy->hitBloodType = liquid_1;
		enemy->anBloodType = gas_1;
	}
	else if (enemy->enemyType == rabbit) 
	{
		enemy->hitBloodType = gas_1;
		enemy->anBloodType = solid_1;
	}
	else
	{
		enemy->hitBloodType = solid_1; 
		enemy->anBloodType = liquid_1;
	}
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	safe_delete(randCreate);

	return enemy;
}

Enemy* Enemy::Create()
{
	Enemy* enemy = new Enemy();
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->enemyType = randCreate->getRandInt(vampire, rabbit);
	
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);
	if (enemy->enemyType == vampire)
	{
		enemy->hitBloodType = liquid_1;
		enemy->anBloodType = gas_1;
	}
	else if (enemy->enemyType == rabbit)
	{
		enemy->hitBloodType = gas_1;
		enemy->anBloodType = solid_1;
	}
	else
	{
		enemy->hitBloodType = solid_1;
		enemy->anBloodType = liquid_1;
	}
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	safe_delete(randCreate);

	return enemy;
}

unique_ptr<Enemy> Enemy::UniqueCreate( int tipe)
{
	unique_ptr<Enemy> enemy = make_unique<Enemy>();

	
	enemy->enemyType = tipe;
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);
	if (enemy->enemyType == vampire)
	{
		enemy->hitBloodType = liquid_1;
		enemy->anBloodType = gas_1;
	}
	else if (enemy->enemyType == rabbit)
	{
		enemy->hitBloodType = gas_1;
		enemy->anBloodType = solid_1;
	}
	else
	{
		enemy->hitBloodType = solid_1;
		enemy->anBloodType = liquid_1;
	}
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	safe_delete(randCreate);

	return move(enemy);

}

unique_ptr<Enemy> Enemy::UniqueCreate()
{
	unique_ptr<Enemy> enemy = make_unique<Enemy>();

	
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);
	enemy->enemyType = randCreate->getRandInt(vampire, rabbit);
	if (enemy->enemyType == vampire)
	{
		enemy->hitBloodType = liquid_1;
		enemy->anBloodType = gas_1;
	}
	else if (enemy->enemyType == rabbit)
	{
		enemy->hitBloodType = gas_1;
		enemy->anBloodType = solid_1;
	}
	else
	{
		enemy->hitBloodType = solid_1;
		enemy->anBloodType = liquid_1;
	}

	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	safe_delete(randCreate);

	return move(enemy);
}

void Enemy::Update()
{
	moveLength -= moveAddLength;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + 640.f;
	pos.y = pos.y + 360.f;
	sprite->SetPosition(pos);

	
}

void Enemy::Draw()
{
	sprite->Draw();
}