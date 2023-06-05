#include "RabbitEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"

RabbitEnemy::~RabbitEnemy()
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

std::unique_ptr<RabbitEnemy> RabbitEnemy::UniqueCreate()
{
	std::unique_ptr<RabbitEnemy> enemy = std::make_unique<RabbitEnemy>();

	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();
	enemy->angle = randCreate->getRandFloat(0, 359);
	enemy->moveLength = randCreate->getRandFloat(400, 500);

	enemy->hitBloodType = gas_1;
	enemy->anBloodType = solid_1;

	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;
	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::rabbit_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::rabbit_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::rabbit_back, backAnimationCount, enemy->pos);

	safe_delete(randCreate);
	return move(enemy);
	
}

void RabbitEnemy::Update()
{
	moveLength -= moveAddLength;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = pos.x + movePoint.x;
	pos.y = pos.y + movePoint.y;
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

int RabbitEnemy::BloodHit(int num)
{
	int temp = num;
	if (GetBloodHitFlag() == true)
	{
		if (GetBloodType() == GetHitBloodType())
		{
			SetDead(TRUE);
			temp--;
		}
		else if (GetBloodType() == GetAnBloodType())
		{
			SetMoveAddLength(2.f);
		}
		else
		{
			SetMoveAddLength(0.5f);
		}
	}
	else
	{
		SetMoveAddLength(1.f);
	}

	return temp;
}

void RabbitEnemy::Draw()
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

	//アングルで移動方向を判定し、判定した方向に向いたアニメーションを使用
	if (angle > 45 && angle < 135) {
		backSprites_[backAnimationCounter_]->Draw();
	}
	else if (angle > 225 && angle < 270) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}
	else {
		besideSprites_[besideAnimationCounter_]->Draw();
	}
}
