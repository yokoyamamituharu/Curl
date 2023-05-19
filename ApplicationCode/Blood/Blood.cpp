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

Blood* Blood::Create(DirectX::XMFLOAT2 position, Temperature temp)
{
	Blood* instance = new Blood();
	instance->position_ = position;
	instance->sprites_[(int)Temperature::solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position, {}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position, {}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position, {}, { 0.5,0.5 });
	instance->temp_ = (int)temp;
	return instance;
}

std::unique_ptr<Blood> Blood::UniquePtrCreate(DirectX::XMFLOAT2 position, Temperature state, DirectX::XMFLOAT2 goal, DirectX::XMFLOAT2* playerPos)
{
	std::unique_ptr<Blood> instance = std::make_unique<Blood>();
	instance->position_ = position;
	instance->goal_ = goal;
	instance->playerPos_ = playerPos;
	instance->sprites_[(int)Temperature::solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position, {1.f,1.f,1.f,1.f}, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
	instance->sprites_[(int)Temperature::gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position, { 1.f,1.f,1.f,1.f }, { 0.5,0.5 });
	instance->temp_ = (int)state;
	DirectX::XMVECTOR vec = { instance->goal_.x - instance->position_.x,instance->goal_.y - instance->position_.y };
	vec = DirectX::XMVector3Normalize(vec);
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

	DirectX::XMVECTOR vec;
	DirectX::XMFLOAT2 vec2;
	float a = 0, b = 0;

	switch (state_)
	{
	case (int)State::idle:

		break;

	case (int)State::shot:
		//ååÇîÚÇŒÇ∑
		vec = { goal_.x - position_.x,goal_.y - position_.y };
		vec = DirectX::XMVector3Normalize(vec);
		a = vec.m128_f32[0];
		b = oldvec_.m128_f32[0];
		if (fabs(a - b) <= 0.001f * fmax(1, fmax(fabs(a), fabs(b)))) {
			vec2 = { vec.m128_f32[0],vec.m128_f32[1] };
			position_ = { position_.x + vec2.x * speed_ ,position_.y + vec2.y * speed_ };

			vec = { goal_.x - position_.x,goal_.y - position_.y };
			vec = DirectX::XMVector3Normalize(vec);
			a = vec.m128_f32[0];
			b = oldvec_.m128_f32[0];
			if (fabs(a - b) >= 0.001f * fmax(1, fmax(fabs(a), fabs(b)))) {
				position_ = goal_;
				state_ = (int)State::idle;
			}
		}
		break;

	case (int)State::back:
		vec = { playerPos_->x - position_.x,playerPos_->y - position_.y };
		vec = DirectX::XMVector3Normalize(vec);
		oldvec_ = vec;
		vec2 = { vec.m128_f32[0],vec.m128_f32[1] };
		position_ = { position_.x + vec2.x * speed_ ,position_.y + vec2.y * speed_ };

		vec = { playerPos_->x - position_.x,playerPos_->y - position_.y };
		vec = DirectX::XMVector3Normalize(vec);
		a = vec.m128_f32[0];
		b = oldvec_.m128_f32[0];
		if (fabs(a - b) >= 0.001f * fmax(1, fmax(fabs(a), fabs(b)))) {
			position_ = *playerPos_;
			state_ = (int)State::heat;
		}
		break;
	default:
		break;
	}

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
	sprites_[temp_]->Draw();
}

bool Blood::GetDead()
{
	return isDead;
}

void Blood::SetDead()
{
	isDead = true;
}