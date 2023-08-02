#include "Player.h"
#include "SafeDelete.h"
#include "KeyInput.h"
#include "ImageManager.h"
#include "MouseInput.h"
#include "PadInput.h"
#include <math.h>
#include "KeyInputHandler.h"
#include "BaseEnemy.h"
#include "SoundManager.h"

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

Player* Player::Create(Vector2 pos, float rote, int hp, int maxBlood[], int speed[]) {
	Player* instance = new Player();
	instance->heatWave_ = Sprite::Create(UINT(ImageManager::ImageName::heatWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->heatWave_->SetPosition({ 500,500 });
	instance->coldWave_ = Sprite::Create(UINT(ImageManager::ImageName::coldWaveNumber), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	instance->coldWave_->SetPosition({ 500,500 });

	instance->state_ = (int)State::idle;
	instance->handler_ = new KeyInputHandler();
	instance->handler_->Initialize(instance);
	instance->position_ = pos;
	instance->playerHp_ = hp;
	for (int i = 0; i < 5; i++) {
		instance->ultMaxBlood_[i] = maxBlood[i];
		instance->ultSpeed_[i] = speed[i];
	}
	instance->bloodGauge_ = maxBlood[0];
	instance->speed_ = float(maxBlood[0]);
	instance->frontSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfForwardWalk, frontAnimationCount, instance->position_);
	instance->backSprites_ = Player::SpritesCreateP((int)ImageManager::ImageName::wolfBackwardWalk, backAnimationCount, instance->position_);
	instance->useAnimation_ = (int)AnimationType::front;
	return instance;
}

void Player::Update(ScrollCamera* camera) {
	//�t���O�������Ă��錌������
	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});

	isMove_ = Move(camera);

	//��ʊO�ɏo�Ȃ��悤�ɂ��鏈��			
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

	speed_ = float(ultSpeed_[ultLevel_]);
	maxBlood_ = ultMaxBlood_[ultLevel_];

	//�v���C���[�̃L�[�C�x���g�X�V
	//handler_->PlayerHandleInput();

	//�M�g�A���g�̏���
	Wave();

	//������o
	//Shot(camera);
	//�g���錌�̎c�ʂ��v�Z
	bloodGauge_ = maxBlood_ - (int)bloods_.size();

	// �̉��ő�ŃE���g���
	if (ultGauge >= ultMaxGauge) {
		//��񂾂����s���鏈��		
		if (ultState == false) {
			if (ultLevel_ < 5) {

			}
			ultLevel_++;
			ultCharge_ = maxUltCharge_;
			//maxBlood_ += 20;
			//speed_ += 4;
		}
		ultState = true;
		// �̉�0�ŃE���g����
	}
	else if (0 >= ultGauge) {
		if (ultState)
		{
			//maxBlood_ -= 10;
			//speed_ -= 2;
		}
		ultState = false;
	}


	// �E���g��ԂȂ�X�e�[�^�X��ς���
	if (ultState == true) {
		ultDiray--;
		// ���ԂŃQ�[�W���炷
		if (ultDiray <= 0) {
			ultGauge--;			// �Q�[�W�������Ă���
			ultDiray = maxUltDiray;
		}
	}
	else if (ultState == false) {
		//speed_ = initSpeed_; // ���̃X�s�[�h�ɖ߂�
	}

	if (ultLevel_ > 0&& ultState) {
		ultChargeDray_--;		
		if (ultCharge_ <= 0) {			
			ultCharge_--;
			ultChargeDray_ = maxUltChargeDray_;
			if (ultCharge_ <= 0) {
				ultLevel_--;
				ultCharge_ = maxUltCharge_;
			}
		}
	}

	/// <summary>
	///�Q�[���ɂ͊֌W�Ȃ�
	/// </summary>
	/// <param name="camera"></param>
	for (std::unique_ptr<Blood>& blood : bloods_) {
		if (KeyInput::GetIns()->TriggerKey(DIK_B) && blood->GetState() == (int)Blood::State::idle) {
			//blood->SetDead();
		}
		//����߂�
		if (isRecall_ && blood->GetTemperature() == (int)Blood::Temperature::liquid && blood->GetState() != (int)Blood::State::back && blood->GetState() != (int)Blood::State::shot) {
			blood->SetState(Blood::State::back);
		}
		//�����v���C���[�̈ʒu�ɖ߂�����v���C���[�̑̉����グ��������
		if (blood->GetState() == (int)Blood::State::heat) {
			// �E���g��ԂłȂ���΃Q�[�W�𑝂₵�Ă���
			if (ultState == false) {
				ultGauge++;

				// �̉����ő�l�𒴂��Ȃ��悤�ɂ���
				if (ultGauge > ultMaxGauge) {
					ultGauge = ultMaxGauge;
				}
			}
			ultCharge_++;
			blood->SetDead();
		}

		XMFLOAT2 pos1 = position_;
		XMFLOAT2 pos2 = blood->GetPosition();
		//�M�g�ƌ��̓����蔻��
		float length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (heatExtend_ / 2 + 16 > length && isHeatWave_&&blood->GetState()!=(int)Blood::State::back&& blood->GetState() != (int)Blood::State::shot) blood->HeatWaveOnCollision();
		//���g�ƌ��̓����蔻��
		length = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
		if (coldExtend_ / 2 + 16 > length && isColdWave_ && blood->GetState() != (int)Blood::State::back && blood->GetState() != (int)Blood::State::shot) blood->ColdWaveOnCollision();

		//���̍X�V����
		blood->Update();
	}
	//�X�v���C�g�̍��W�̍X�V
	heatWave_->SetPosition(position_);
	coldWave_->SetPosition(position_);
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(position_);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(position_);
	}
}

void Player::Shot(ScrollCamera* camera, Vector2 pos) {
	//�����ő吔�o���Ă����珈�����X�L�b�v
	if (bloods_.size() >= maxBlood_) return;

	if (MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK) && shotDiray_ <= 0 || PadInput::GetIns()->TriggerButton(PadInput::Button_RS) && shotDiray_ <= 0) {
		constexpr float playerYSize = 60.f;
		if (pos.x != -100.0f) {
			bloods_.push_back(Blood::UniquePtrCreate({ position_.x,position_.y - playerYSize / 2 }, Blood::Temperature::liquid, pos, &position_));
			// SE
			SoundManager::GetIns()->PlaySE(SoundManager::SEKey::syukketu, 0.1f);
		}
		else {
			Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();
			bloods_.push_back(Blood::UniquePtrCreate({ position_.x,position_.y - playerYSize / 2 }, Blood::Temperature::liquid, cursolPos, &position_));
		}
		shotDiray_ = maxShotDiray_;
	}
	else {
		shotDiray_--;
	}

}

void Player::Draw(ScrollCamera* scroll) {
	//���̕`��
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}

	//�A�j���[�V�����̏���
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

	//���E�̌���������
	if (useDirectionSide_ == (int)AnimationType::RightSide) {
		frontSprites_[frontAnimationCounter_]->SetIsFlipX(true);
		backSprites_[backAnimationCounter_]->SetIsFlipX(false);
	}
	else if (useDirectionSide_ == (int)AnimationType::LeftSide) {
		frontSprites_[frontAnimationCounter_]->SetIsFlipX(false);
		backSprites_[backAnimationCounter_]->SetIsFlipX(true);
	}

	//�A���O���ňړ������𔻒肵�A���肵�������Ɍ������A�j���[�V�������g�p
	if (useAnimation_ == (int)AnimationType::back) {
		backSprites_[backAnimationCounter_]->Draw();
	}
	else if (useAnimation_ == (int)AnimationType::front) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}
	//�M�g�̕`��
	if (isHeatWave_) heatWave_->Draw();
	//���g�̕`��
	if (isColdWave_) coldWave_->Draw();
}

void Player::AddPlayerVector(Vector2 vec) {
	position_ = { position_.x + vec.x,position_.y + vec.y };
}

bool Player::Move(ScrollCamera* camera) {
	if (KeyInput::GetIns()->PushKey(DIK_W) || PadInput::GetIns()->leftStickY() <= -0.5f) {
		Vector2 cursolPos = MouseInput::GetIns()->ClientToPostEffect() + camera->GetPosition();
		Vector2 playerPos = position_;
		//�v���C���[�ƖړI�n�i�J�[�\���̈ʒu�j���߂�������ړ����������Ȃ��i�v���C���[���J�[�\���̈ʒu�ŉ������J��Ԃ��Ă��܂�����j
		float length = sqrtf((cursolPos.x - playerPos.x) * (cursolPos.x - playerPos.x) + (cursolPos.y - playerPos.y) * (cursolPos.y - playerPos.y));
		if (length > 1.0f) {
			Vector2 vec = cursolPos - playerPos;
			vec.normalize();
			AddPlayerVector(vec * speed_);

			//�g���摜��I��
			if (vec.y > 0) {
				//���Ɉړ�
				useAnimation_ = (int)AnimationType::front;
			}
			else if (vec.y < 0) {
				//��Ɉړ�
				useAnimation_ = (int)AnimationType::back;
			}
			if (vec.x > 0) {
				//�E�Ɉړ�
				useDirectionSide_ = (int)AnimationType::RightSide;
			}
			else if (vec.x < 0) {
				//���Ɉړ�
				useDirectionSide_ = (int)AnimationType::LeftSide;
			}
		}
		return true;
	}

	return false;
}

void Player::Wave() {
	//���t���[���ŏ���false�ɂ���
	isRecall_ = false;
	//�M�g�����
	if (KeyInput::GetIns()->TriggerKey(DIK_E)) {
		isHeatWave_ = true;
		SoundManager::GetIns()->PlaySE(SoundManager::SEKey::neppa, 0.3f);
	}
	//���g�����
	if (KeyInput::GetIns()->TriggerKey(DIK_Q)) {
		SoundManager::GetIns()->PlaySE(SoundManager::SEKey::kanpa, 0.5f);
		isColdWave_ = true;
	}

	if (isHeatWave_) {
		heatWave_->SetSize({ heatExtend_ ,heatExtend_ });
		heatWave_->SetAlpha(heatAlpha_);
		heatExtend_ += 240;
		heatAlpha_ -= 0.1f;
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
