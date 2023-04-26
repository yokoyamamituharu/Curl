#pragma once
#include <DirectXMath.h>
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Easing.h"
#include "SafeDelete.h"

class BaseScene
{
public:
	//�f�X�g���N�^
	virtual ~BaseScene() {}

public: //���z�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;

protected: //���z�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	virtual void SceneChange() = 0;

public: //�����o�֐�

	/// <summary>
	/// �}�E�X���X�v���C�g�ɐG��Ă��邩(�摜�̒��S���)
	/// </summary>
	/// <param name="mousePos">�}�E�X�̈ʒu</param>
	/// <param name="spritePos">�X�v���C�g�̈ʒu</param>
	/// <param name="spriteWidth">�X�v���C�g����</param>
	/// <param name="spriteHeight">�X�v���C�g�c��</param>
	/// <returns>�}�E�X���X�v���C�g��G��Ă���</returns>
	bool IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight);

protected: //�ÓI�����o�ϐ�

};