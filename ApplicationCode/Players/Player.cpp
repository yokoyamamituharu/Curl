#include "Player.h"
#include "SafeDelete.h"
#include "KeyInput.h"
#include "ImageManager.h"
#include "MouseInput.h"
#include <math.h>
#include "KeyInputHandler.h"

Player::Player()
{
}

Player::~Player()
{
	for (auto sprite : sprites_) {
		delete sprite.second;
	}
	sprites_.clear();
	safe_delete(handler);
}

Player* Player::Create()
{
	Player* instance = new Player();
	instance->sprites_[(int)State::idle] = Sprite::Create(UINT(ImageManager::ImageName::playerTexNumber), { 0,0 },{},{0.5,0.5 });
	instance->sprites_[(int)State::idle]->SetSize({ 128, 128 });
	instance->sprites_[(int)State::heat] = Sprite::Create(UINT(ImageManager::ImageName::playerHeatTexNumber), { 0,0 }, {}, { 0.5,0.5 });
	instance->sprites_[(int)State::heat]->SetSize({ 128, 128 });
	instance->state_ = (int)State::idle;
	instance->handler = new KeyInputHandler();
	instance->handler->Initialize(instance);
	return instance;
}

void Player::Update()
{
	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});
	if (heat_ > 0) {
		state_ = (int)State::heat;
		speed_ = 7.0f;
		heatDiray_--;
		if (heatDiray_ <= 0) {
			heat_--;
			heatDiray_ = maxHeatDiray_;
		}
	}
	else {
		state_ = (int)State::idle;
		speed_ = 2.0f;
	}


	DirectX::XMVECTOR vec = {};
	//if (KeyInput::GetIns()->PushKey(DIK_D))	vec.m128_f32[0] += speed;
	//if (KeyInput::GetIns()->PushKey(DIK_A))	vec.m128_f32[0] -= speed;
	//if (KeyInput::GetIns()->PushKey(DIK_W))	vec.m128_f32[1] -= speed;
	//if (KeyInput::GetIns()->PushKey(DIK_S))	vec.m128_f32[1] += speed;

	handler->PlayerHandleInput();

	position_ = { position_.x + vec.m128_f32[0],position_.y + vec.m128_f32[1] };

	//ååÇï˙èo
	Shot();

	for (std::unique_ptr<Blood>& blood : bloods_) {
		if (KeyInput::GetIns()->TriggerKey(DIK_B)) {
			blood->SetDead();
		}
		if (KeyInput::GetIns()->TriggerKey(DIK_G)) {
			blood->SetState(Blood::State::back);
		}
		if (blood->GetState() == (int)Blood::State::heat) {
			heat_++;
			blood->SetDead();
		}
		XMFLOAT2 pos1 = position_;
		XMFLOAT2 pos2 = blood->GetPosition();
		float length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (200.0f > length) {
			if (KeyInput::GetIns()->TriggerKey(DIK_0)) {
				blood->Rising();
			}
			if (KeyInput::GetIns()->TriggerKey(DIK_9)) {
				blood->Decrease();
			}
		}
		blood->Update();
	}

	sprites_[state_]->SetPosition(position_);
}

void Player::Shot()
{
	XMFLOAT2 cursolPos = DirectX::XMFLOAT2{ float(MouseInput::GetIns()->GetMousePoint().x)-camera_->GetPosition().x,
		float(MouseInput::GetIns()->GetMousePoint().y) - camera_->GetPosition().y };
	XMFLOAT2 playerPos = position_;
	DirectX::XMVECTOR vec3 = { cursolPos.x - playerPos.x,cursolPos.y - playerPos.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	XMFLOAT2 vec2 = { vec3.m128_f32[0],vec3.m128_f32[1] };

	int x = 0;
	int x2 = 10;
	int time = 0.1;

	int vec = x2 * time;

	shotDiray_--;
	if (KeyInput::GetIns()->PushKey(DIK_SPACE) && shotDiray_ <= 0) {
		bloods_.push_back(Blood::UniquePtrCreate({ position_ }, Blood::Temperature::solid, cursolPos, &position_));
		shotDiray_ = maxShotDiray_;
	}
}

void Player::Draw(ScrollCamera* scroll)
{
	//sprites_[state_]->SetPosition({ position_.x - scroll.x , position_.y - scroll.y });
	sprites_[state_]->Draw(scroll);
	//sprites_[state_]->SetPosition({ position_.x + scroll.x , position_.y + scroll.y });
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}
}

void Player::AddPlayerVector(Vector2 vec)
{
	position_ = { position_.x + vec.x,position_.y + vec.y };
}
