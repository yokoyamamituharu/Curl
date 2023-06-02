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
	safe_delete(handler_);
}

Player* Player::Create()
{
	Player* instance = new Player();
	instance->sprites_[(int)State::idle] = Sprite::Create(UINT(ImageManager::ImageName::playerTexNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->sprites_[(int)State::idle]->SetSize({ 128, 128 });
	instance->sprites_[(int)State::heat] = Sprite::Create(UINT(ImageManager::ImageName::playerHeatTexNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->sprites_[(int)State::heat]->SetSize({ 128, 128 });
	instance->heatWave_ = Sprite::Create(UINT(ImageManager::ImageName::playerHeatTexNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	//instance->neppa->SetSize({ 128, 128 });
	instance->state_ = (int)State::idle;
	instance->handler_ = new KeyInputHandler();
	instance->handler_->Initialize(instance);
	instance->position_ = { 0,0 };
	instance->maxBlood_ = 10;
	instance->bloodGauge_ = instance->maxBlood_;
	return instance;
}

Player* Player::Create(Vector2 pos, float rote, int hp, int maxBlood)
{
	Player* instance = new Player();
	instance->sprites_[(int)State::idle] = Sprite::Create(UINT(ImageManager::ImageName::playerTexNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->sprites_[(int)State::idle]->SetSize({ 128, 128 });
	instance->sprites_[(int)State::heat] = Sprite::Create(UINT(ImageManager::ImageName::playerHeatTexNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->sprites_[(int)State::heat]->SetSize({ 128, 128 });
	instance->heatWave_ = Sprite::Create(UINT(ImageManager::ImageName::heatWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->heatWave_->SetPosition({ 500,500 });
	instance->coldWave_ = Sprite::Create(UINT(ImageManager::ImageName::coldWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->coldWave_->SetPosition({ 500,500 });
	instance->state_ = (int)State::idle;
	instance->handler_ = new KeyInputHandler();
	instance->handler_->Initialize(instance);
	instance->position_ = pos;
	instance->playerHp_ = hp;
	instance->maxBlood_ = maxBlood;
	instance->bloodGauge_ = maxBlood;
	return instance;
}

void Player::Update(ScrollCamera* camera)
{
	//フラグが立っている血を消す
	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});

	//プレイヤーのキーイベント更新
	handler_->PlayerHandleInput();

	//オーバーロード状態
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

	//血を放出
	Shot(camera);

	bloodGauge_ = maxBlood_ - bloods_.size();

	for (std::unique_ptr<Blood>& blood : bloods_) {
		if (KeyInput::GetIns()->TriggerKey(DIK_B) && blood->GetState() == (int)Blood::State::idle) {
			blood->SetDead();
		}
		if (KeyInput::GetIns()->TriggerKey(DIK_G) && blood->GetTemperature() == (int)Blood::Temperature::liquid) {
			blood->SetState(Blood::State::back);
		}
		if (blood->GetState() == (int)Blood::State::heat) {
			heat_++;
			blood->SetDead();
		}

		XMFLOAT2 pos1 = position_;
		XMFLOAT2 pos2 = blood->GetPosition();
		//熱波
		float length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (heatExtend / 2 + 16 > length && isHeatWave) blood->HeatWaveOnCollision();
		//寒波
		length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (coldExtend / 2 + 16 > length && isColdWave) blood->ColdWaveOnCollision();

		blood->Update();
	}

	//熱波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_E)) isHeatWave = true;
	//寒波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_Q)) isColdWave = true;

	if (isHeatWave) {
		heatWave_->SetSize({ heatExtend ,heatExtend });
		heatWave_->SetAlpha(heatAlpha);
		heatExtend += 40;
		heatAlpha -= 0.1;
		if (heatAlpha < 0) {
			isHeatWave = false;
			heatExtend = 0;
			heatAlpha = 1;
		}
	}
	if (isColdWave) {
		coldWave_->SetSize({ coldExtend ,coldExtend });
		coldWave_->SetAlpha(coldAlpha);
		coldExtend += 40;
		coldAlpha -= 0.1f;
		if (coldAlpha < 0) {
			isColdWave = false;
			coldExtend = 0;
			coldAlpha = 1;
		}
	}

	heatWave_->SetPosition(position_);
	coldWave_->SetPosition(position_);

	sprites_[state_]->SetPosition(position_);
}

void Player::Shot(ScrollCamera* camera)
{
	if (bloods_.size() >= maxBlood_) return;
	XMFLOAT2 cursolPos = DirectX::XMFLOAT2{ float(MouseInput::GetIns()->GetMousePoint().x) - camera->GetPosition().x,
		float(MouseInput::GetIns()->GetMousePoint().y) - camera->GetPosition().y };
	XMFLOAT2 playerPos = position_;
	DirectX::XMVECTOR vec3 = { cursolPos.x - playerPos.x,cursolPos.y - playerPos.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	XMFLOAT2 vec2 = { vec3.m128_f32[0],vec3.m128_f32[1] };

	if (KeyInput::GetIns()->PushKey(DIK_SPACE) && shotDiray_ <= 0) {
		bloods_.push_back(Blood::UniquePtrCreate({ position_ }, Blood::Temperature::solid, cursolPos, &position_));
		shotDiray_ = maxShotDiray_;
	}
	else {
		shotDiray_--;
	}
}

void Player::Draw(ScrollCamera* scroll)
{
	sprites_[state_]->Draw();
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}
	if (isHeatWave) heatWave_->Draw();
	if (isColdWave) coldWave_->Draw();
}

void Player::AddPlayerVector(Vector2 vec)
{
	position_ = { position_.x + vec.x,position_.y + vec.y };
}
