#include "BasiliskEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
BasiliskEnemy::~BasiliskEnemy()
{
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++)
	{
		safe_delete(besideSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
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
	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_back, backAnimationCount, enemy->pos);

	enemy->moveFlag = randCreate->getRandInt(0, 1);
	safe_delete(randCreate);
	return move(enemy);
}

void BasiliskEnemy::Update()
{
	moveLength -= moveAddLength;

	if (moveFlag == TRUE)
	{
		angle += moveAngle;
	}
	else
	{
		angle -= moveAngle;

	}
	if (angle > maxAngle.size())
	{
		angle -= maxAngle.size();
	}
	if (angle < minAngle.size())
	{
		angle += maxAngle.size();
	}

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + centerPoint.x;
	pos.y = pos.y + centerPoint.y;
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		besideSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(pos);
	}
}

void BasiliskEnemy::Draw()
{
	if (++animationTimer_ > animationTime) {
		frontAnimationCounter_++;
		besideAnimationCounter_++;
		backAnimationCounter_++;
		animationTimer_ = 0;
	}

	if (frontAnimationCounter_ >= frontAnimationCount) {
		frontAnimationCounter_ = 0;
	}
	if (besideAnimationCounter_ >= besideAnimationCount) {
		besideAnimationCounter_ = 0;
	}
	if (backAnimationCounter_ >= backAnimationCount) {
		backAnimationCounter_ = 0;
	}

	frontSprites_[frontAnimationCounter_]->Draw();
	//besideSprites_[besideAnimationCounter_]->Draw();
	//backSprites_[backAnimationCounter_]->Draw();
}


