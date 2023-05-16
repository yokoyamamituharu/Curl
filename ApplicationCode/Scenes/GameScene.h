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
#include "Enemy.h"

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

private: //�����o�ϐ�
	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect> postEffect_;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo_;
	//�n��
	std::unique_ptr<Object3d> ground_;
	//���C�g
	std::unique_ptr<LightGroup> light_;
	//�e�L�X�g�`��
	TextDraw* text_;

	Blood* blood_ = nullptr;
	Player* player_ = nullptr;
	Tower* tower_ = nullptr;
	Sprite* bgSprite_ = nullptr;
	
	Enemy* enemy_{};

	Enemys* enemys_{};
	list<unique_ptr<Enemy>> enemy_1;
};

