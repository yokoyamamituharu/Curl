#include "Player.h"
#include "SafeDelete.h"
#include "KeyInput.h"
#include "ImageManager.h"
#include "MouseInput.h"
#include "PadInput.h"
#include <math.h>
#include "KeyInputHandler.h"
#include "BaseEnemy.h"

int32_t Player::frontAnimationCount = 6;
int32_t Player::backAnimationCount = 6;
int32_t Player::animationTime = 10;

Player::Player()
{
}

Player::~Player()
{
	for (auto sprite : sprites_) {
		delete sprite.second;
	}
	sprites_.clear();
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
	safe_delete(handler_);
	safe_delete(handler_);
	safe_delete(heatWave_);
	safe_delete(coldWave_);
}

std::vector<Sprite*> Player::SpritesCreateP(int imageName, int32_t animationCount, Vector2& enemyPos)
{
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, enemyPos));
		sprites[i]->SetAnchorPoint({ 0.5f, 0.5f });
		sprites[i]->SetPosition(enemyPos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 128 * (float)i;
		sprites[i]->SetSize({ 128.0f, 128.0f });
		sprites[i]->SetTextureRect(texBase, { 128.0f, 128.0f });
	}
	return sprites;
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
	instance->frontSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfForwardWalk, frontAnimationCount, instance->position_);
	instance->backSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfBackwardWalk, backAnimationCount, instance->position_);
	return instance;
}

void Player::Update(ScrollCamera* camera)
{
	//フラグが立っている血を消す
	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});

	Move(camera);
	//アングルで移動方向を判定し、判定した方向に向いたアニメーションを使用
	if (angle == 10) {
		useAnimation = (int)AnimationType::front;
	}
	else if (angle == 0) {
		useAnimation = (int)AnimationType::back;
	}

	//プレイヤーのキーイベント更新
	//handler_->PlayerHandleInput();

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

	Wave();

	//血を放出
	Shot(camera);
	//血の残量
	bloodGauge_ = maxBlood_ - bloods_.size();

	/// <summary>
	///ゲームには関係ない
	/// </summary>
	/// <param name="camera"></param>
	for (std::unique_ptr<Blood>& blood : bloods_) {
		if (KeyInput::GetIns()->TriggerKey(DIK_B) && blood->GetState() == (int)Blood::State::idle) {
			//blood->SetDead();
		}
		//血を戻す
		if (isRecall_ && blood->GetTemperature() == (int)Blood::Temperature::liquid) {
			blood->SetState(Blood::State::back);
		}
		//血がプレイヤーの位置に戻ったらプレイヤーの体温を上げ（未実装）血を消す
		if (blood->GetState() == (int)Blood::State::heat) {
			heat_++;
			blood->SetDead();
		}

		XMFLOAT2 pos1 = position_;
		XMFLOAT2 pos2 = blood->GetPosition();
		//熱波と血の当たり判定
		float length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (heatExtend / 2 + 16 > length && isHeatWave) blood->HeatWaveOnCollision();
		//寒波と血の当たり判定
		length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (coldExtend / 2 + 16 > length && isColdWave) blood->ColdWaveOnCollision();

		blood->Update();
	}
	heatWave_->SetPosition(position_);
	coldWave_->SetPosition(position_);
	sprites_[state_]->SetPosition(position_);
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(position_);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(position_);
	}
}

void Player::Shot(ScrollCamera* camera)
{
	if (bloods_.size() >= maxBlood_) return;
	if (MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK) || PadInput::GetIns()->TriggerButton(PadInput::Button_RS) && shotDiray_ <= 0) {
		Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();


		bloods_.push_back(Blood::UniquePtrCreate({ position_.x,position_.y - 30 }, Blood::Temperature::liquid, cursolPos, &position_));
		shotDiray_ = maxShotDiray_;
	}
	else {
		shotDiray_--;
	}
}

void Player::Draw(ScrollCamera* scroll)
{
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}
	if (++animationTimer_ > animationTime) {
		frontAnimationCounter_++;
		backAnimationCounter_++;
		animationTimer_ = 0;
	}

	if (frontAnimationCounter_ >= frontAnimationCount) {
		frontAnimationCounter_ = 0;
	}
	if (backAnimationCounter_ >= backAnimationCount) {
		backAnimationCounter_ = 0;
	}
	//sprites_[state_]->Draw();
	//アングルで移動方向を判定し、判定した方向に向いたアニメーションを使用
	if (useAnimation == (int)AnimationType::back) {
		backSprites_[backAnimationCounter_]->Draw();
	}
	else if (useAnimation == (int)AnimationType::front) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}


	if (isHeatWave) heatWave_->Draw();
	if (isColdWave) coldWave_->Draw();
}

void Player::AddPlayerVector(Vector2 vec)
{
	position_ = { position_.x + vec.x,position_.y + vec.y };
}

void Player::Move(ScrollCamera* camera)
{
	float wariaiX = 0.925;
	float wariaiY = 0.85;

	Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();
	Vector2 playerPos = position_;
	DirectX::XMVECTOR vec3 = { cursolPos.x - playerPos.x,cursolPos.y - playerPos.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	Vector2 vec2 = { vec3.m128_f32[0],vec3.m128_f32[1] };

	if (KeyInput::GetIns()->PushKey(DIK_W) || PadInput::GetIns()->leftStickY() <= -0.5f) {
		AddPlayerVector(vec2 * speed_);
		if (vec2.y > 0) {
			//下に移動
			angle = 10;
		}
		else if (vec2.y < 0) {
			//上に移動
			angle = 0;
		}
	}
}

void Player::Wave()
{
	//毎フレーム最初にfalseにする
	isRecall_ = false;
	//熱波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_E)) isHeatWave = true;
	//寒波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_Q)) isColdWave = true;

	if (isHeatWave) {
		heatWave_->SetSize({ heatExtend ,heatExtend });
		heatWave_->SetAlpha(heatAlpha);
		heatExtend += 240;
		heatAlpha -= 0.1;
		if (heatAlpha < 0) {
			isHeatWave = false;
			isRecall_ = true;
			heatExtend = 0;
			heatAlpha = 1;
		}
	}
	if (isColdWave) {
		coldWave_->SetSize({ coldExtend ,coldExtend });
		coldWave_->SetAlpha(coldAlpha);
		coldExtend += 240;
		coldAlpha -= 0.1f;
		if (coldAlpha < 0) {
			isColdWave = false;
			isRecall_ = true;
			coldExtend = 0;
			coldAlpha = 1;
		}
	}
}
