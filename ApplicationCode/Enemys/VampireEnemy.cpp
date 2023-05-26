#include "VampireEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
VampireEnemy::~VampireEnemy()
{
	safe_delete(sprite);
}

std::unique_ptr<VampireEnemy> VampireEnemy::UniqueCreate()
{
	std::unique_ptr<VampireEnemy> enemy = std::make_unique<VampireEnemy>();


	
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);

	enemy->hitBloodType = liquid_1;
	enemy->anBloodType = gas_1;


	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->sprite = Sprite::Create(vampire, enemy->pos);
	enemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
	enemy->sprite->SetPosition(enemy->pos);
	
	safe_delete(randCreate);
	return move(enemy);
}

void VampireEnemy::Update()
{

	moveLength -= moveAddLength;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + 640.f;
	pos.y = pos.y + 360.f;
	sprite->SetPosition(pos);
}

void VampireEnemy::Draw()
{
	sprite->Draw();
}

