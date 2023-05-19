#include "Blood.h"
#include "ImageManager.h"
#include <list>
#include "KeyInput.h"
#include <numeric>

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

std::unique_ptr<Blood> Blood::UniquePtrCreate(DirectX::XMFLOAT2 position, STATE state, DirectX::XMFLOAT2 goal)
{
	std::unique_ptr<Blood> instance = std::make_unique<Blood>();
	instance->startPosition_ = position;
	instance->position_ = position;
	instance->goal_ = goal;
	instance->sprites_[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position,{ 1.f,1.f,1.f,1.f }, { 0.5f,0.5f });
	instance->sprites_[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5f,0.5f });
	instance->sprites_[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5f,0.5f });
	instance->state_ = state;
	return std::move(instance);
}

void Blood::Update()
{
	//çXêVèàóù
	//deadTimer--;
	if (deadTimer < 0)isDead = true;

	if (KeyInput::GetIns()->TriggerKey(DIK_UP)) { Rising(); }
	if (KeyInput::GetIns()->TriggerKey(DIK_DOWN)) { Decrease(); }

	//position_ = { position_.x + vec_.x ,position_.y + vec_.y };
	position_ = Learp(startPosition_, goal_, time_);
	if (time_ < 1) time_ += 0.1f;
	sprites_[state_]->SetPosition(position_);
}

void Blood::Rising()
{
	if (state_ == gas)return;
	else state_++;
}

void Blood::Decrease()
{
	if (state_ == solid)return;
	else state_--;
}


void Blood::Draw()
{
	sprites_[state_]->Draw();
}

bool Blood::GetDead()
{
	return isDead;
}

void Blood::SetDead()
{
	isDead = true;
}

DirectX::XMFLOAT2 Blood::Learp(DirectX::XMFLOAT2 p, DirectX::XMFLOAT2 p2, float time)
{
	p2.x -= p.x;
	p2.y -= p.y;
	DirectX::XMFLOAT2 p3{};
	p3.x = p2.x * time + p.x;
	p3.y = p2.y * time + p.y;
	return p3;
}
