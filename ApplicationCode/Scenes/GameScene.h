#pragma once
#include "BaseScene.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Object3d.h"
#include "Vector3.h"
#include "Camera.h"
#include "MouseInput.h"
#include "Easing.h"
#include "Shapes.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "DebugText.h"
#include "MotionMath.h"
#include "SceneManager.h"
#include "TextDraw.h"
#include "JsonLoader.h"
#include"Enemys.h"

#include "Blood.h"
#include "Player.h"
#include "Tower.h"
#include "ScrollCamera.h"

#include "Button.h"
#include"Collision.h"
class GameScene : public BaseScene
{
public: //�����o�֐�
	/// <summary>
	/// �������֐�
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���ƓG�̓����蔻��
	/// </summary>
	void HitBloodAndEnemys();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	void HitEnemys();

private: //�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

	void RoadPlayer();

private: //�����o�ϐ�
	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect> postEffect_;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo_;
	//���C�g
	std::unique_ptr<LightGroup> light_;
	//�e�L�X�g�`��
	TextDraw* text_;

	Player* player_ = nullptr;
	Tower* tower_ = nullptr;
	Sprite* bgSprite_ = nullptr;
	Sprite* GameSprite1 = nullptr;
	Sprite* GameSprite2 = nullptr;
	Sprite* GameSprite3 = nullptr;
	std::unique_ptr<Sprite> bloodGaugeSprite_ = nullptr;
	
	Enemys* enemys_{};
	
	ScrollCamera* scrollCamera_ = nullptr;

	std::unique_ptr<Button> button_;
	std::unique_ptr<Button>	poseButton_;
	std::unique_ptr<Button>	poseBackButton_;
	std::unique_ptr<Button>	titleButton_;

	bool pose_ = false;
};

