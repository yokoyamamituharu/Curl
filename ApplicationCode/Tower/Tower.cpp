#include "Tower.h"
#include "ImageManager.h"

void Tower::Initialize(int32_t hp)
{
	hit = 0;
	hitTime = 10;
	hp_ = hp;
	pos_ = { 640, 360 };
	tower_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::towerNumber, pos_);
	tower_->SetAnchorPoint({ 0.5f,0.5f });
}

void Tower::Update()
{
	if (hit)
	{
		hitTime--;
		if (hitTime < 0)
		{
			hit = 0;
			hitTime = 10;
		}
	}
}

void Tower::Draw()
{
	DirectX::XMMATRIX mat = {};
	//tower_->SetRotation(90);
	if (hitTime % 2 == 0)
	{
		tower_->Draw();

	}
}

void Tower::OnCollision()
{
	hit = 1;
	hp_--;
}
