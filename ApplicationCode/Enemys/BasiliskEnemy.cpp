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
	safe_delete(markerSprite_);
}

std::unique_ptr<BasiliskEnemy> BasiliskEnemy::UniqueCreate(Cell cell)
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

	//�㉺
	if (randCreate->getRandInt(0, 10) % 2 == 0)
	{
		//��
		if (randCreate->getRandInt(0, 10) % 2 == 0)
		{
			enemy->dPos_.X = 0;
			enemy->dPos_.Y = randCreate->getRandInt(0, 43);
			enemy->useAnimation = AnimationType::rightSide;
		}
		//�E
		else
		{
			enemy->dPos_.X = 51;
			enemy->dPos_.Y = randCreate->getRandInt(0, 43);
			enemy->useAnimation = AnimationType::ReftSide;
		}
	}
	//���E
	else
	{
		//��
		if (randCreate->getRandInt(0, 10) % 2 == 0)
		{
			enemy->dPos_.X = randCreate->getRandInt(0, 52);
			enemy->dPos_.Y = 0;
			enemy->useAnimation = AnimationType::front;
		}
		//��
		else
		{
			enemy->dPos_.X = randCreate->getRandInt(0, 52);
			enemy->dPos_.Y = 42;
			enemy->useAnimation = AnimationType::back;
		}
	}


	enemy->pos.x = (float)enemy->dPos_.X * (float)enemy->chipSize;
	enemy->pos.y = (float)enemy->dPos_.Y * (float)enemy->chipSize;


	enemy->gorl = cell;
	enemy->route = AStar::GetInstance()->AStarActivate(enemy->dPos_, enemy->gorl);

	enemy->frontSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_front, frontAnimationCount, enemy->pos);
	enemy->besideSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_beside, besideAnimationCount, enemy->pos);
	enemy->backSprites_ = SpritesCreate(ImageManager::ImageName::basilisk_back, backAnimationCount, enemy->pos);

	enemy->markerSprite_ = Sprite::Create((UINT)ImageManager::ImageName::guideArrow, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	enemy->markerSprite_->SetSize({ 56,87 });
	enemy->markerSprite_->SetUi(true);

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

	for (auto cell : route)
	{

		Vector2 vec;
		vec.x = (cell.X * chipSize + 32) - pos.x;
		vec.y = (cell.Y * chipSize + 32) - pos.y;
		vec.normalize();
		//2�_�Ԃ̃x�N�g���i���K�����Ăˁj
		pos.x += vec.x;
		pos.y += vec.y;
		//�}�b�v�`�b�v��̓G�̈ʒu���X�V
		dPos_.X = pos.x / chipSize;
		dPos_.Y = pos.y / chipSize;

		//�G�̈ʒu���Q�ƃZ���Ɠ����ɂȂ����烊�X�g����폜
		if (dPos_.X == cell.X && dPos_.Y == cell.Y) {
			route.erase(route.begin());
		}

		break;
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

void BasiliskEnemy::Draw(bool isInvisible)
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
	if (!isInvisible) {
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
	}
	if (isMarker_) {
		markerSprite_->Draw();
	}
}


