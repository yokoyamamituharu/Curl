#include"Enemy.h"


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

	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
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

	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	return enemy;
}

unique_ptr<Enemy> Enemy::UniqueCreate()
{
	unique_ptr<Enemy> enemy = make_unique<Enemy>();

	
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);
	enemy->enemyType = randCreate->getRandInt(individual, gas);

	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(enemy->enemyType, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	return enemy;
}

void Enemy::Update()
{
	moveLength--;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;

	sprite->SetPosition(pos);
}

void Enemy::Draw()
{
	sprite->Draw();
}