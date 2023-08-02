#pragma once
#include "BaseScene.h"
#include "Button.h"
#include "PostEffect.h"

class SelectScene : public BaseScene
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

private: //���z�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange() override;

private: //�ÓI�����o�ϐ�
	//�C�[�W���O����
	static const float easingTime;

private: //�����o�ϐ�
	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect> postEffect_;
	//�`���[�g���A���{�^��
	std::unique_ptr<Button> tutorial_;
	//�X�e�[�W1�{�^��
	std::unique_ptr<Button> stage1_;
	// �w�i�摜
	std::unique_ptr<Sprite> stageSelect_ = nullptr;
	// �X�e�[�W�I���E�B���h�E
	std::unique_ptr<Sprite> stageSelectWindow_ = nullptr;
	//�C�[�W���O�^�C�}�[
	float easingTimer_;
};

