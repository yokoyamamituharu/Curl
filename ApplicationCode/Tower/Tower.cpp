#include "Tower.h"
#include "ImageManager.h"

void Tower::Initialize(int32_t hp)
{
	hp_ = hp;
	pos_ = { 640, 360 };
	tower_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::towerNumber, pos_);
	tower_->SetAnchorPoint({ 0.5f,0.5f });
}

void Tower::Update()
{
}

void Tower::Draw()
{
	DirectX::XMMATRIX mat = {};
	tower_->SetRotation(90);
	tower_->Draw();
}

void Tower::OnCollision()
{
	hp_--;
}
