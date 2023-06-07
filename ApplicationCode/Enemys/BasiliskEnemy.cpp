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
{//作成開始
	std::unique_ptr<BasiliskEnemy> enemy = std::make_unique<BasiliskEnemy>();

	//randの生成
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();

	//血のタイプ代入
	enemy->hitBloodType = solid_1;
	enemy->anBloodType = liquid_1;

	//エネミーの値代入
	enemy->angle = randCreate->getRandFloat(0, 359);//角度のランダム代入
	enemy->moveLength = randCreate->getRandFloat(400, 500);//movePointからどれだけ離れているかのランダム代入

	//座標の計算代入
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;

	//座標のずれを修正
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;

	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_back, backAnimationCount, enemy->pos);

	enemy->moveFlag = randCreate->getRandInt(0, 1);


	//randの開放
	safe_delete(randCreate);

	//エネミー代入
	return move(enemy);
}


void BasiliskEnemy::Update()
{

	//フラグが立っているとアングルが加算そうでなければ減算
	if (moveFlag == TRUE)angle += moveAngle;
	else angle -= moveAngle;

	//アングルが360を超えたら360引く
	if (angle > maxAngle.size())angle -= maxAngle.size();
	
	//アングルが0を下回ったら360足す
	if (angle < minAngle.size())angle += maxAngle.size();

	//距離の計算
	moveLength -= moveAddLength;

	//座標の計算代入
	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;

	//座標のずれを修正
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


