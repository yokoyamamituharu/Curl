#include "BaseEnemy.h"
#include "SafeDelete.h"
#include"Collision.h"

std::vector<Sprite*> BaseEnemy::SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& enemyPos)
{
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, enemyPos));
		sprites[i]->SetAnchorPoint({ 0.5f, 0.5f });
		sprites[i]->SetPosition(enemyPos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 64.0f * (float)i;
		sprites[i]->SetSize({ 64.0f, 64.0f });
		sprites[i]->SetTextureRect(texBase, { 64.0f, 64.0f });
	}
	return sprites;
}

void BaseEnemy::WorldMarker(XMFLOAT2 camera)
{

#pragma region �G�̕`�悪�X�N���[���̊O�ōs���Ă��邩�̔���
	//�X�N���[���̍ŏ��l�@- 32
	//�X�N���[���̍ő�l�@+ 32
	//��̓�̒��Ƀv���C���[�����邩�̔���
	isMarker_ = false;
	isLeft_ = false;
	isRight_ = false;
	isUp_ = false;
	isDown_ = false;
	//�G�̉摜�̔����̃T�C�Y
	float radiusSize = 32;

	if (pos.x < camera.x - radiusSize)
	{
		isMarker_ = true;
		isLeft_ = true;
	}
	if (pos.x > WinApp::window_width + camera.x + radiusSize)
	{
		isMarker_ = true;
		isRight_ = true;
	}

	if (pos.y < camera.y - radiusSize)
	{
		isMarker_ = true;
		isUp_ = true;
	}
	if (pos.y > WinApp::window_height + camera.y + radiusSize)
	{
		isMarker_ = true;
		isDown_ = true;
	}
#pragma endregion �`�悪�X�N���[���̊O�ōs���Ă��邩�̔���

#pragma region �}�[�J�[���o�����߂̏���

	if (isLeft_ || isRight_) {
		if (isUp_ == false && isDown_ == false) {
			markerPos_.y = pos.y - camera.y;
			if (markerPos_.y < 32) {
				markerPos_.y = 32;
			}
			if (markerPos_.y > WinApp::window_height - 32) {
				markerPos_.y = WinApp::window_height - 32;
			}
		}
	}

	if (isUp_ || isDown_) {
		if (isLeft_ == false && isRight_ == false) {
			markerPos_.x = pos.x - camera.x;
			if (markerPos_.x < 32) {
				markerPos_.x = 32;
			}
			if (markerPos_.x > WinApp::window_width - radiusSize - 96) {
				markerPos_.x = WinApp::window_width - radiusSize - 96;
			}
		}
	}

	if (isLeft_) {
		markerPos_.x = radiusSize;
	}
	else if (isRight_) {
		markerPos_.x = WinApp::window_width - radiusSize - 96;
	}

	if (isUp_) {
		markerPos_.y = radiusSize;
	}
	else if (isDown_) {
		markerPos_.y = WinApp::window_height - radiusSize;
	}

	//��ʂ̒������W
	Vector2 screenCenter = { camera.x + WinApp::window_width / 2,camera.y + WinApp::window_height };
	//�����̈ʒu�����ʂ̒��S�ւ̃x�N�g��
	Vector2 vec = screenCenter - pos;
	vec.normalize();
	// atan2 ���g�p���Ċp�x���擾
	markerAngle = atan2f(vec.x, vec.y);
	//�p�x�����W�A������x�֕ϊ�
	markerAngle = markerAngle * 180.0f / 3.14f;
	//�␳�l�𑫂�
	float PI = -1;
	markerAngle *= PI;

#pragma endregion �}�[�J�[���o�����߂̏���

	}