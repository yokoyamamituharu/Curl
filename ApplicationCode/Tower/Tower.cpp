#include "Tower.h"
#include "ImageManager.h"

void Tower::Initialize(int32_t hp)
{
	hp_ = hp;
	pos_ = { 590, 360 };
	tower_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::towerNumber, pos_);
}

void Tower::Update()
{
}

void Tower::Draw()
{
	tower_->Draw();
}

void Tower::OnCollision()
{
	hp_--;
}
