#include "Blood.h"
#include "ImageManager.h"
#include <list>

Blood::Blood()
{
}

Blood::~Blood()
{
	for (auto sprite : sprites_) {
		delete sprite.second;
	}
	sprites_.clear();
}

Blood* Blood::Create(DirectX::XMFLOAT2 position, STATE state)
{
	Blood* instance = new Blood();
	instance->position_ = position;
	instance->sprites_[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
	instance->sprites_[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
	instance->sprites_[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
	instance->state_ = state;
	return instance;
}

std::unique_ptr<Blood> Blood::UniquePtrCreate(DirectX::XMFLOAT2 position, STATE state, DirectX::XMFLOAT2 vec)
{
	std::unique_ptr<Blood> instance = std::make_unique<Blood>();
	instance->position_ = position;
	instance->vec_ = vec;
	instance->sprites_[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
	instance->sprites_[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
	instance->sprites_[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
	instance->state_ = state;
	return std::move(instance);
}

void Blood::Update()
{
	//XVˆ—
	deadTimer--;
	if (deadTimer < 0)isDead = true;

	position_ = { position_.x + vec_.x ,position_.y + vec_.y };
	sprites_[state_]->SetPosition(position_);
}

void Blood::Rising()
{
	if (state_ >= gas)return;
	state_++;
}

void Blood::Decrease()
{
	if (state_ <= solid)return;
	state_--;
}


void Blood::Draw()
{
	sprites_[state_]->Draw();
}

bool Blood::GetDead()
{
	return isDead;
}
