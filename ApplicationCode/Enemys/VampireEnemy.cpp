#include "VampireEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
VampireEnemy::~VampireEnemy()
{
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		safe_delete(besideSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
	safe_delete(markerSprite_);
}

std::unique_ptr<VampireEnemy> VampireEnemy::UniqueCreate()
{
	//作成開始
	std::unique_ptr<VampireEnemy> enemy = std::make_unique<VampireEnemy>();

	//randの生成
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();

	//血のタイプ代入
	enemy->hitBloodType = liquid_1;
	enemy->anBloodType = gas_1;

	////エネミーの値代入
	enemy->angle = randCreate->getRandFloat(0, 359);//角度のランダム代入
	enemy->moveLength = randCreate->getRandFloat(400, 500);//movePointからどれだけ離れているかのランダム代入

	////座標の計算代入
	//enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	//enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;

	/*enemy->dPos_.X = randCreate->getRandInt(0, 52);
	enemy->dPos_.Y = randCreate->getRandInt(0, 43);*/

	enemy->dPos_.X = 20;
	enemy->dPos_.Y = 5;

	enemy->pos.x = (float)enemy->dPos_.X * (float)enemy->chipSize;
	enemy->pos.y = (float)enemy->dPos_.Y * (float)enemy->chipSize;


	enemy->routeTime = 100;
	enemy->gorl = { 4,2 };
	enemy->route = AStar::GetInstance()->AStarActivate(enemy->dPos_, enemy->gorl);
	//座標のずれを修正
	/*enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;*/

	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::vampire_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::vampire_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::vampire_back, backAnimationCount, enemy->pos);

	enemy->markerSprite_ = Sprite::Create((UINT)ImageManager::ImageName::guideArrow, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	enemy->markerSprite_->SetSize({ 56,87 });
	enemy->markerSprite_->SetUi(true);

	//randの開放
	safe_delete(randCreate);

	//エネミー代入
	return move(enemy);
}

void VampireEnemy::Update()
{
	//距離の計算
	moveLength -= moveAddLength;

	routeTime--;
	if (routeTime < 0)
	{

		route = AStar::GetInstance()->AStarActivate(dPos_, gorl);
		routeTime = 100;
	}
	////座標の計算代入
	//pos.y = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	//pos.x = cos((angle * DirectX::XM_PI) / 180) * moveLength;


	//座標のずれを修正
	pos.x = pos.x + movePoint.x;
	pos.y = pos.y + movePoint.y;

	for (auto cell : route)
	{
		//2点間のベクトル（正規化してね）
		pos.x += pos.x - (cell.X * chipSize);
		pos.y += pos.y - (cell.Y * chipSize);
		Vector2 vec = pos;
		pos = vec.normalize();
		//マップチップ上の敵の位置を更新
		dPos_.X = pos.x / chipSize;
		dPos_.Y = pos.y / chipSize;

		//敵の位置が参照セルと同じになったらリストから削除
		if (dPos_.X == cell.X && dPos_.Y == cell.Y) {
			route.erase(route.begin());
		}

		break;
	}


	//アングルで移動方向を判定し、判定した方向に向いたアニメーションを使用
	if (angle > 45 && angle < 135) {
		useAnimation = AnimationType::back;
	}
	else if (angle > 225 && angle < 270) {
		useAnimation = AnimationType::front;
	}
	else if (angle >= 135 && angle <= 225) {
		useAnimation = AnimationType::rightSide;
	}
	else {
		useAnimation = AnimationType::ReftSide;

	}

	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		besideSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(pos);
	}
	markerSprite_->SetPosition(markerPos_);
	markerSprite_->SetRotation(markerAngle);
}

void VampireEnemy::Draw(bool isInvisible)
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
	if (!isInvisible) {
		if (useAnimation == AnimationType::back) {
			backSprites_[backAnimationCounter_]->Draw();
		}
		else if (useAnimation == AnimationType::front) {
			frontSprites_[frontAnimationCounter_]->Draw();
		}
		else if (useAnimation == AnimationType::rightSide) {
			besideSprites_[besideAnimationCounter_]->SetIsFlipX(true);
			besideSprites_[besideAnimationCounter_]->Draw();
		}
		else {
			besideSprites_[besideAnimationCounter_]->SetIsFlipX(false);
			besideSprites_[besideAnimationCounter_]->Draw();
		}
	}
	if (isMarker_) {
		markerSprite_->Draw();
	}
}

