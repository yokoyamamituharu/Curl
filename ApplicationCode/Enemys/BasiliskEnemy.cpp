#include "BasiliskEnemy.h"
#include"SafeDelete.h"
#include"RandCreate.h"
BasiliskEnemy::~BasiliskEnemy()
{
	for (int32_t i = 0; i < frontAnimationCount; i++) {
		safe_delete(frontSprites_[i]);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++)
	{
		safe_delete(besideSprites_[i]);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		safe_delete(backSprites_[i]);
	}
}

std::unique_ptr<BasiliskEnemy> BasiliskEnemy::UniqueCreate()
{//�쐬�J�n
	std::unique_ptr<BasiliskEnemy> enemy = std::make_unique<BasiliskEnemy>();

	//rand�̐���
	RandCreate* randCreate = new RandCreate();
	randCreate->Ins();

	//���̃^�C�v���
	enemy->hitBloodType = solid_1;
	enemy->anBloodType = liquid_1;

	//�G�l�~�[�̒l���
	enemy->angle = randCreate->getRandFloat(0, 359);//�p�x�̃����_�����
	enemy->moveLength = randCreate->getRandFloat(400, 500);//movePoint����ǂꂾ������Ă��邩�̃����_�����

	//���W�̌v�Z���
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;

	//���W�̂�����C��
	enemy->pos.x = enemy->pos.x + 640.f;
	enemy->pos.y = enemy->pos.y + 360.f;

	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_back, backAnimationCount, enemy->pos);

	enemy->moveFlag = randCreate->getRandInt(0, 1);


	//rand�̊J��
	safe_delete(randCreate);

	//�G�l�~�[���
	return move(enemy);
}


void BasiliskEnemy::Update()
{

	//�t���O�������Ă���ƃA���O�������Z�����łȂ���Ό��Z
	if (moveFlag == TRUE)angle += moveAngle;
	else angle -= moveAngle;

	//�A���O����360�𒴂�����360����
	if (angle > maxAngle.size())angle -= maxAngle.size();
	
	//�A���O����0�����������360����
	if (angle < minAngle.size())angle += maxAngle.size();

	//�����̌v�Z
	moveLength -= moveAddLength;

	//���W�̌v�Z���
	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.y = cos((angle * DirectX::XM_PI) / 180) * moveLength;

	//���W�̂�����C��
	pos.x = pos.x + movePoint.x;
	pos.y = pos.y + movePoint.y;

	for (int32_t i = 0; i < frontAnimationCount; i++) {
		frontSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < besideAnimationCount; i++) {
		besideSprites_[i]->SetPosition(pos);
	}
	for (int32_t i = 0; i < backAnimationCount; i++) {
		backSprites_[i]->SetPosition(pos);
	}
}

void BasiliskEnemy::Draw()
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
	if (angle > 45 && angle < 135) {
		backSprites_[backAnimationCounter_]->Draw();
	}
	else if (angle > 225 && angle < 270) {
		frontSprites_[frontAnimationCounter_]->Draw();
	}
	else {
		besideSprites_[besideAnimationCounter_]->Draw();
	}
}


