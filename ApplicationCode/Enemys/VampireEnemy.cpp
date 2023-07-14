#include "VampireEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
VampireEnemy::~VampireEnemy()
{
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		safe_delete(besideSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
	safe_delete(markerSprite_);
}

std::unique_ptr<VampireEnemy> VampireEnemy::UniqueCreate()
{
	//�쐬�J�n
	std::unique_ptr<VampireEnemy> enemy = std::make_unique<VampireEnemy>();

	//rand�̐���
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();

	//���̃^�C�v���
	enemy->hitBloodType = liquid_1;
	enemy->anBloodType = gas_1;

	//�G�l�~�[�̒l���
	enemy->angle = randCreate->getRandFloat(0, 359);//�p�x�̃����_�����
	enemy->moveLength = randCreate->getRandFloat(400, 500);//movePoint����ǂꂾ������Ă��邩�̃����_�����

	//���W�̌v�Z���
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;

	//���W�̂�����C��
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;

	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::vampire_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::vampire_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::vampire_back, backAnimationCount, enemy->pos);

	enemy->markerSprite_ = Sprite::Create((UINT)ImageManager::ImageName::guideArrow, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	enemy->markerSprite_->SetSize({ 56,87 });
	enemy->markerSprite_->SetUi(true);

	//rand�̊J��
	safe_delete(randCreate);

	//�G�l�~�[���
	return move(enemy);
}

void VampireEnemy::Update()
{
	//�����̌v�Z
	moveLength -= moveAddLength;


	//���W�̌v�Z���
	pos.y = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x = cos((angle * DirectX::XM_PI) / 180) * moveLength;

	//���W�̂�����C��
	pos.x = pos.x + movePoint.x;
	pos.y = pos.y + movePoint.y;

	//�A���O���ňړ������𔻒肵�A���肵�������Ɍ������A�j���[�V�������g�p
	if (angle > 45 && angle < 135) {
		useAnimation = AnimationType::back;
	}
	else if (angle > 225 && angle < 270) {
		useAnimation = AnimationType::front;
	}
	else if (angle >= 135 && angle <= 225) {
		useAnimation = AnimationType::rightSide;
	}
	else {
		useAnimation = AnimationType::ReftSide;

	}

	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		besideSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(pos);
	}
	markerSprite_->SetPosition(markerPos_);
	markerSprite_->SetRotation(markerAngle);
}

void VampireEnemy::Draw()
{
	if (++animationTimer_ > animationTime) {
		frontAnimationCounter_++;
		besideAnimationCounter_++;
		backAnimationCounter_++;
		animationTimer_ = 0;
	}

	if (frontAnimationCounter_ >= frontAnimationCount) {
		frontAnimationCounter_ = 0;
	}
	if (besideAnimationCounter_ >= besideAnimationCount) {
		besideAnimationCounter_ = 0;
	}
	if (backAnimationCounter_ >= backAnimationCount) {
		backAnimationCounter_ = 0;
	}

	//�A���O���ňړ������𔻒肵�A���肵�������Ɍ������A�j���[�V�������g�p
	if (useAnimation == AnimationType::back) {
		backSprites_[backAnimationCounter_]->Draw();
	}
	else if (useAnimation == AnimationType::front) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}
	else if (useAnimation == AnimationType::rightSide) {
		besideSprites_[besideAnimationCounter_]->SetIsFlipX(true);
		besideSprites_[besideAnimationCounter_]->Draw();
	}
	else {
		besideSprites_[besideAnimationCounter_]->SetIsFlipX(false);
		besideSprites_[besideAnimationCounter_]->Draw();
	}
	if (isMarker_) {
		markerSprite_->Draw();
	}
}

