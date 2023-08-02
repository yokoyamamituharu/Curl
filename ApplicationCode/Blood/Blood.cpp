#include "Blood.h"
#include "ImageManager.h"
#include <list>
#include "KeyInput.h"
#include <numeric>
#include "Vector2.h"


Blood::~Blood()
{
	for (auto sprite : sprites_) {
		delete sprite.second;
	}
	sprites_.clear();
}

Blood* Blood::Create(DirectX::XMFLOAT2 position, Temperature temp)
{
	Blood* instance = new Blood();
	instance->position_ = position;
	instance->sprites_[(int)Temperature::solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position, {}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position, {}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position, {}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::droppedLiquid] = Sprite::Create(UINT(ImageManager::ImageName::droppedLiquid), position, {}, { 0.5,0.5 });
	instance->temp_ = (int)temp;
	return instance;
}

std::unique_ptr<Blood> Blood::UniquePtrCreate(Vector2 position, Temperature state, Vector2 targetPos_, Vector2* playerPos)
{
	std::unique_ptr<Blood> instance = std::make_unique<Blood>();
	instance->position_ = position;
	instance->targetPos_ = targetPos_;
	instance->playerPos_ = playerPos;
	instance->sprites_[(int)Temperature::solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
 
	instance->sprites_[(int)Temperature::droppedLiquid] = Sprite::Create(UINT(ImageManager::ImageName::droppedLiquid), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
	instance->temp_ = (int)state;
	Vector2 vec = instance->targetPos_ - instance->position_;
	vec.normalize();
	instance->oldvec_ = vec;
	instance->state_ = (int)State::shot;
	return std::move(instance);
}

void Blood::Update()
{
	//çXêVèàóù
	//deadTimer--;
	if (deadTimer_ < 0)isDead = true;

	if (KeyInput::GetIns()->TriggerKey(DIK_UP))  Rising();
	if (KeyInput::GetIns()->TriggerKey(DIK_DOWN))  Decrease();
	DirectX::XMINT4 a1{}, a2{};
	Vector2 vec{  };	

	switch (state_)
	{
	case (int)State::idle:

		break;

	case (int)State::shot:
		position_ += oldvec_ * speed_;
		vec = targetPos_ - position_;
		vec.normalize();
		a1.x = int(vec.x * 10000) / 1000;
		a1.y = int(vec.x * 10000) / 100 - a1.x * 10;
		a1.z = int(vec.y * 10000) / 1000;
		a1.w = int(vec.y * 10000) / 100 - a1.z * 10;
		a2.x = int(oldvec_.x * 10000) / 1000;
		a2.y = int(oldvec_.x * 10000) / 100 - a2.x * 10;
		a2.z = int(oldvec_.y * 10000) / 1000;
		a2.w = int(oldvec_.y * 10000) / 100 - a2.z * 10;

		if (!(a1.x == a2.x && a1.y == a2.y) || !(a1.z == a2.z && a1.w == a2.w)) {
			state_ = (int)State::idle;
			position_ = targetPos_;
		}

		break;

	case (int)State::back:
		vec = *playerPos_ - position_;
		vec.normalize();
		position_ += vec * speed_;
		oldvec_ = vec;
		vec = *playerPos_ - position_;
		vec.normalize();
		a1.x = int(vec.x * 10000) / 1000;
		a1.y = int(vec.x * 10000) / 100 - a1.x * 10;
		a1.z = int(vec.y * 10000) / 1000;
		a1.w = int(vec.y * 10000) / 100 - a1.z * 10;
		a2.x = int(oldvec_.x * 10000) / 1000;
		a2.y = int(oldvec_.x * 10000) / 100 - a2.x * 10;
		a2.z = int(oldvec_.y * 10000) / 1000;
		a2.w = int(oldvec_.y * 10000) / 100 - a2.z * 10;

		if (!(a1.x == a2.x && a1.y == a2.y) || !(a1.z == a2.z && a1.w == a2.w)) {
			state_ = (int)State::heat;
			position_ = *playerPos_;
		}
		break;
	default:
		break;
	}
	if (tempDray > 0) {
		tempDray--;
	}

	sprites_[(int)Temperature::droppedLiquid]->SetPosition(position_);
	sprites_[temp_]->SetPosition(position_);
}

void Blood::Rising()
{
	if (temp_ >= (int)Temperature::gas)return;
	temp_++;
}

void Blood::Decrease()
{
	if (temp_ <= (int)Temperature::solid)return;
	temp_--;
}


void Blood::Draw()
{
	if (state_ == (int)State::idle && temp_ <= (int)Temperature::liquid) {
		sprites_[(int)Temperature::droppedLiquid]->Draw();
	}
	else {
		sprites_[temp_]->Draw();
	}
}

bool Blood::GetDead()
{
	return isDead;
}

void Blood::SetDead()
{
	isDead = true;
}

void Blood::HeatWaveOnCollision()
{
	if (tempDray <= 0) {
		Rising();
		tempDray = maxTempDray;
	}
}

void Blood::ColdWaveOnCollision()
{
	if (tempDray <= 0) {
		Decrease();
		tempDray = maxTempDray;
	}
}
