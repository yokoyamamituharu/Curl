#include "BasiliskEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
BasiliskEnemy::~BasiliskEnemy()
{
	safe_delete(sprite);

}

std::unique_ptr<BasiliskEnemy> BasiliskEnemy::UniqueCreate()
{
	std::unique_ptr<BasiliskEnemy> enemy = std::make_unique<BasiliskEnemy>();



	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);

	enemy->hitBloodType = solid_1;
	enemy->anBloodType = liquid_1;



	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(basilisk, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);

	safe_delete(randCreate);
	return move(enemy);
}

void BasiliskEnemy::Update()
{
	moveLength -= moveAddLength;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + 640.f;
	pos.y = pos.y + 360.f;
	sprite->SetPosition(pos);
}

void BasiliskEnemy::Draw()
{
	sprite->Draw();
}


