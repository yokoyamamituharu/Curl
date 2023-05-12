#include "Blood.h"
#include "ImageManager.h"
#include <list>
#include "KeyInput.h"
#include <numeric>

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
	instance->position_ = position;
	instance->goal_ = goal;
	instance->sprites_[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
	instance->sprites_[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
	instance->sprites_[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
	instance->state_ = state;
	DirectX::XMVECTOR vec3 = { instance->goal_.x - instance->position_.x,instance->goal_.y - instance->position_.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	instance->oldvec = vec3;
	return std::move(instance);
}

void Blood::Update()
{
	//XVˆ—
	//deadTimer--;
	if (deadTimer < 0)isDead = true;

	if (KeyInput::GetIns()->TriggerKey(DIK_UP)) { Rising(); }
	if (KeyInput::GetIns()->TriggerKey(DIK_DOWN)) { Decrease(); }

	//ŒŒ‚ğ”ò‚Î‚·
	DirectX::XMVECTOR vec3 = { goal_.x - position_.x,goal_.y - position_.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	float a = vec3.m128_f32[0];
	float b = oldvec.m128_f32[0];
	if (fabs(a - b) <= 0.001f * fmax(1, fmax(fabs(a), fabs(b)))) {
		DirectX::XMFLOAT2 vec2 = { vec3.m128_f32[0],vec3.m128_f32[1] };
		position_ = { position_.x + vec2.x * speed_ ,position_.y + vec2.y * speed_ };

		vec3 = { goal_.x - position_.x,goal_.y - position_.y };
		vec3 = DirectX::XMVector3Normalize(vec3);
		a = vec3.m128_f32[0];
		b = oldvec.m128_f32[0];
		if (fabs(a - b) >= 0.001f * fmax(1, fmax(fabs(a), fabs(b)))) {
			position_ = goal_;
		}		
	}	

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

void Blood::SetDead()
{
	isDead = true;
}