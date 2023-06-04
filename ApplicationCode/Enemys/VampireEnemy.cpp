#include "VampireEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
VampireEnemy::~VampireEnemy()
{
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites[i]);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		safe_delete(besideSprites[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites[i]);
	}
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
	enemy->frontSprites = SpritesCreate(ImageManager::ImageName::vampire_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites = SpritesCreate(ImageManager::ImageName::vampire_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites = SpritesCreate(ImageManager::ImageName::vampire_back, backAnimationCount, enemy->pos);
	
	safe_delete(randCreate);
	return move(enemy);
}

void VampireEnemy::Update()
{

	moveLength -= moveAddLength;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + centerPoint.x;
	pos.y = pos.y + centerPoint.y;
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		besideSprites[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites[i]->SetPosition(pos);
	}
}

void VampireEnemy::Draw()
{
	frontSprites[0]->Draw();
}

