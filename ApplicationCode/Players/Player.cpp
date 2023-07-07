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

Player::~Player() {
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
	safe_delete(handler_);
	safe_delete(handler_);
	safe_delete(heatWave_);
	safe_delete(reticle_);
	safe_delete(coldWave_);
}

std::vector<Sprite*> Player::SpritesCreateP(int imageName, int32_t animationCount, Vector2& pos) {
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, pos));
		sprites[i]->SetAnchorPoint({ 0.5f, 0.5f });
		sprites[i]->SetPosition(pos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 128 * (float)i;
		sprites[i]->SetSize({ 128.0f, 128.0f });
		sprites[i]->SetTextureRect(texBase, { 128.0f, 128.0f });
	}
	return sprites;
}

Player* Player::Create(Vector2 pos, float rote, int hp, int maxBlood) {
	Player* instance = new Player();
	instance->heatWave_ = Sprite::Create(UINT(ImageManager::ImageName::heatWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->heatWave_->SetPosition({ 500,500 });
	instance->coldWave_ = Sprite::Create(UINT(ImageManager::ImageName::coldWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->coldWave_->SetPosition({ 500,500 });
	instance->reticle_ = Sprite::Create(UINT(ImageManager::ImageName::reticle), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->reticle_->SetPosition({ 500,500 });

	instance->state_ = (int)State::idle;
	instance->handler_ = new KeyInputHandler();
	instance->handler_->Initialize(instance);
	instance->position_ = pos;
	instance->playerHp_ = hp;
	instance->maxBlood_ = maxBlood;
	instance->bloodGauge_ = maxBlood;
	instance->frontSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfForwardWalk, frontAnimationCount, instance->position_);
	instance->backSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfBackwardWalk, backAnimationCount, instance->position_);
	instance->useAnimation_ = (int)AnimationType::front;
	return instance;
}

void Player::Update(ScrollCamera* camera) {

	XMFLOAT2 mouse;
	mouse.x = (float)MouseInput::GetIns()->GetMousePoint().x;
	mouse.y = (float)MouseInput::GetIns()->GetMousePoint().y;
	reticle_->SetPosition(mouse);
	//フラグが立っている血を消す
	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});

	isMove_ = Move(camera);

	//画面外に出ないようにする処理			
	if (position_.x < ScrollCamera::GetMinScreenEdge().x + 32.0f) {
		position_.x = ScrollCamera::GetMinScreenEdge().x + 32.0f;
	}
	if (position_.y < ScrollCamera::GetMinScreenEdge().y + 32.0f) {
		position_.y = ScrollCamera::GetMinScreenEdge().y + 32.0f;
	}

	if (position_.x > ScrollCamera::GetMaxScreenEdge().x - 32.0f) {
		position_.x = ScrollCamera::GetMaxScreenEdge().x - 32.0f;
	}
	if (position_.y > ScrollCamera::GetMaxScreenEdge().y - 32.0f) {
		position_.y = ScrollCamera::GetMaxScreenEdge().y - 32.0f;
	}

	//プレイヤーのキーイベント更新
	//handler_->PlayerHandleInput();

	//熱波、寒波の処理
	Wave();

	//血を放出
	Shot(camera);
	//使える血の残量を計算
	bloodGauge_ = maxBlood_ - bloods_.size();

	// 体温最大でウルト状態
	if (ultGauge >= ultMaxGauge) {
		//一回だけ実行する処理		
		if (ultState == false) {
			maxBlood_ += 20;
			speed_ += 4;
		}
		ultState = true;
		// 体温0でウルト解除
	} else if (0 >= ultGauge) {
		if (ultState)
		{
			maxBlood_ -= 10;
			speed_ -= 2;
		}
		ultState = false;
	}


	// ウルト状態ならステータスを変える
	if (ultState == true) {
		//speed_ = 5.0f;		// スピードを上げる
		ultDiray--;
		// 時間でゲージ減らす
		if (ultDiray <= 0) {
			ultGauge--;			// ゲージを下げていく
			ultDiray = maxUltDiray;
		}
	} else if (ultState == false) {
		//speed_ = initSpeed_; // 元のスピードに戻す
	}

	

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
		//血がプレイヤーの位置に戻ったらプレイヤーの体温を上げ血を消す
		if (blood->GetState() == (int)Blood::State::heat) {
			// ウルト状態でなければゲージを増やしていく
			if (ultState == false) {
				ultGauge++;

				// 体温が最大値を超えないようにする
				if (ultGauge > ultMaxGauge) {
					ultGauge = ultMaxGauge;
				}
			}
			blood->SetDead();
		}

		XMFLOAT2 pos1 = position_;
		XMFLOAT2 pos2 = blood->GetPosition();
		//熱波と血の当たり判定
		float length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (heatExtend_ / 2 + 16 > length && isHeatWave_) blood->HeatWaveOnCollision();
		//寒波と血の当たり判定
		length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (coldExtend_ / 2 + 16 > length && isColdWave_) blood->ColdWaveOnCollision();

		//血の更新処理
		blood->Update();
	}
	//スプライトの座標の更新
	heatWave_->SetPosition(position_);
	coldWave_->SetPosition(position_);
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(position_);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(position_);
	}
}

void Player::Shot(ScrollCamera* camera) {
	//血を最大数出していたら処理をスキップ
	if (bloods_.size() >= maxBlood_) return;
	if (MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK) && shotDiray_ <= 0 || PadInput::GetIns()->TriggerButton(PadInput::Button_RS) && shotDiray_ <= 0) {
		Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();
		bloods_.push_back(Blood::UniquePtrCreate({ position_.x,position_.y - 30 }, Blood::Temperature::liquid, cursolPos, &position_));
		shotDiray_ = maxShotDiray_;
	} else {
		shotDiray_--;
	}
}

void Player::Draw(ScrollCamera* scroll) {
	//血の描画
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}

	//アニメーションの処理
	if (isMove_) {
		if (++animationTimer_ > animationTime) {
			frontAnimationCounter_++;
			backAnimationCounter_++;
			animationTimer_ = 0;
		}
	}

	if (frontAnimationCounter_ >= frontAnimationCount) {
		frontAnimationCounter_ = 0;
	}
	if (backAnimationCounter_ >= backAnimationCount) {
		backAnimationCounter_ = 0;
	}

	//左右の向きを決定
	if (useDirectionSide_ == (int)AnimationType::RightSide) {
		frontSprites_[frontAnimationCounter_]->SetIsFlipX(true);
		backSprites_[backAnimationCounter_]->SetIsFlipX(false);
	} else if (useDirectionSide_ == (int)AnimationType::LeftSide) {
		frontSprites_[frontAnimationCounter_]->SetIsFlipX(false);
		backSprites_[backAnimationCounter_]->SetIsFlipX(true);
	}

	//アングルで移動方向を判定し、判定した方向に向いたアニメーションを使用
	if (useAnimation_ == (int)AnimationType::back) {
		backSprites_[backAnimationCounter_]->Draw();
	} else if (useAnimation_ == (int)AnimationType::front) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}

	reticle_->Draw();
	//熱波の描画
	if (isHeatWave_) heatWave_->Draw();
	//寒波の描画
	if (isColdWave_) coldWave_->Draw();
}

void Player::AddPlayerVector(Vector2 vec) {
	position_ = { position_.x + vec.x,position_.y + vec.y };
}

bool Player::Move(ScrollCamera* camera) {
	if (KeyInput::GetIns()->PushKey(DIK_W) || PadInput::GetIns()->leftStickY() <= -0.5f) {
		Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();
		Vector2 playerPos = position_;
		//プレイヤーと目的地（カーソルの位置）が近かったら移動処理をしない（プレイヤーがカーソルの位置で往復を繰り返してしまうから）
		float length = sqrtf((cursolPos.x - playerPos.x) * (cursolPos.x - playerPos.x) + (cursolPos.y - playerPos.y) * (cursolPos.y - playerPos.y));
		if (length > 1.0f) {
			Vector2 vec = cursolPos - playerPos;
			vec.normalize();
			AddPlayerVector(vec * speed_);

			//使う画像を選ぶ
			if (vec.y > 0) {
				//下に移動
				useAnimation_ = (int)AnimationType::front;
			} else if (vec.y < 0) {
				//上に移動
				useAnimation_ = (int)AnimationType::back;
			}
			if (vec.x > 0) {
				//右に移動
				useDirectionSide_ = (int)AnimationType::RightSide;
			} else if (vec.x < 0) {
				//左に移動
				useDirectionSide_ = (int)AnimationType::LeftSide;
			}
		}
		return true;
	}

	return false;
}

void Player::Wave() {
	//毎フレーム最初にfalseにする
	isRecall_ = false;
	//熱波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_E)) isHeatWave_ = true;
	//寒波を放射
	if (KeyInput::GetIns()->TriggerKey(DIK_Q)) isColdWave_ = true;

	if (isHeatWave_) {
		heatWave_->SetSize({ heatExtend_ ,heatExtend_ });
		heatWave_->SetAlpha(heatAlpha_);
		heatExtend_ += 240;
		heatAlpha_ -= 0.1;
		if (heatAlpha_ < 0) {
			isHeatWave_ = false;
			isRecall_ = true;
			heatExtend_ = 0;
			heatAlpha_ = 1;
		}
	}
	if (isColdWave_) {
		coldWave_->SetSize({ coldExtend_ ,coldExtend_ });
		coldWave_->SetAlpha(coldAlpha_);
		coldExtend_ += 240;
		coldAlpha_ -= 0.1f;
		if (coldAlpha_ < 0) {
			isColdWave_ = false;
			isRecall_ = true;
			coldExtend_ = 0;
			coldAlpha_ = 1;
		}
	}
}
