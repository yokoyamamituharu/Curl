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

#pragma region �`�悪�X�N���[���̊O�ōs���Ă��邩�̔���

	//�X�N���[���̍ŏ��l�@- 32
	//�X�N���[���̍ő�l�@+ 32
	//��̓�̒��Ƀv���C���[�����邩�̔���

#pragma endregion �`�悪�X�N���[���̊O�ōs���Ă��邩�̔���

#pragma region �}�[�J�[���o�����߂̏���

	//��̔���ŊO�ɂ����ꍇ

	//�z�[�~���O�e�Ǝ�������
	
	XMVECTOR vec;

	vec.m128_f32[0] = (camera.x - pos.x);
	vec.m128_f32[1] = (camera.y - pos.y);
	vec = DirectX::XMVector2Normalize(vec);

	markerAdd.m128_f32[0] = vec.m128_f32[0] * markerLength;
	markerAdd.m128_f32[1] = vec.m128_f32[1] * markerLength;

	markerPos.x = pos.x + markerAdd.m128_f32[0];
	markerPos.y = pos.y + markerAdd.m128_f32[1];

#ifdef �t���O����

	if (pos.x < /*�X�N���[���̍ŏ��l - 32*/)
	{
		if (markerPos.x >/*�X�N���[���̍ŏ��l - 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//�t���O�̏I��
		}
	}
	else if (pos.x > /*�X�N���[���̍ő�l + 32*/)
	{
		if (markerPos.x </*�X�N���[���̍ŏ��l + 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//�t���O�̏I��
		}
	}
	else
	{

	}

	if (pos.y < /*�X�N���[���̍ŏ��l - 32*/)
	{
		if (markerPos.y >/*�X�N���[���̍ŏ��l - 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//�t���O�̏I��
		}
	}
	else if (pos.y > /*�X�N���[���̍ő�l + 32*/)
	{
		if (markerPos.y </*�X�N���[���̍ŏ��l + 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//�t���O�̏I��
		}
	}
	else
	{

	}
#endif // �t���O����

	


#pragma endregion �}�[�J�[���o�����߂̏���


	//atan2(pos.x - ((float)WinApp::window_width / 2), pos.y - ((float)WinApp::window_height / 2));
	


}