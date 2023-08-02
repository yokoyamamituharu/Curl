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
#include"EnemyManager.h"
#include "ParticleManager2d.h"

#include "Blood.h"
#include "Player.h"
#include "Tower.h"
#include "ScrollCamera.h"

#include "Button.h"
#include "Collision.h"
#include "Timer.h"
#include "ArrowMarker.h"

#include "MessageWindow.h"
#include "Camera2D.h"
#include "MapChip2D.h"

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
	/// �ԂƓG�̓����蔻��
	/// </summary>
	void HitTowerAndEnemys();

	/// <summary>
	/// �}�b�v�ƃv���C���[�̓����蔻��
	/// </summary>
	void HitMapAndPlayer();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	void HitEnemys();

	Vector2 GetWorldMousePos();

protected: //�ÓI�����o�֐�

	/// <summary>
	/// UI�摜����
	/// </summary>
	/// <param name="imageName">�摜��</param>
	/// <param name="animationCount">�A�j���[�V������</param>
	/// <param name="enemyPos">UI���W</param>
	/// <returns>�A�j���[�V�����X�v���C�g</returns>
	static std::vector<Sprite*> SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& UIpos);

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
	std::unique_ptr<Sprite> bgSprite_ = nullptr;
	std::unique_ptr<Sprite> GameSprite1_ = nullptr;
	std::unique_ptr<Sprite> GameSprite2_ = nullptr;
	std::unique_ptr<Sprite> GameSprite3_ = nullptr;
	Sprite* playerHp = nullptr;
	Timer* timer_;
	std::unique_ptr<Sprite> manual_ = nullptr;
	std::unique_ptr<Sprite> bloodGaugeSprite_ = nullptr;
	std::unique_ptr<Sprite> ultGaugeSprite_[6] = { nullptr };
	DirectX::XMFLOAT3 color[6] = {};
	//std::unique_ptr<Sprite> ultGaugeSprite1_ = nullptr;
	//std::unique_ptr<Sprite> ultGaugeSprite2_ = nullptr;
	//std::unique_ptr<Sprite> ultGaugeSprite3_ = nullptr;
	//std::unique_ptr<Sprite> ultGaugeSprite4_ = nullptr;
	//std::unique_ptr<Sprite> ultGaugeSprite5_ = nullptr;
	//std::unique_ptr<Sprite> overheatSprite_ = nullptr;
	std::unique_ptr<Sprite> reticleSprite_ = nullptr;
	std::unique_ptr<Sprite> towerBreak_[4];
	std::unique_ptr<ParticleManager2d> particle_ = nullptr;
	
	EnemyManager* enemys_{};
	
	ScrollCamera* scrollCamera_ = nullptr;

	std::unique_ptr<Button>	poseButton_;
	std::unique_ptr<Button>	poseBackButton_;
	std::unique_ptr<Button>	titleButton_;
	std::unique_ptr<MessageWindow> messageWindow_;

	bool pose_ = false;
	bool debugMuteki = false;
	Camera2D* camera2D = nullptr;

	MapChip2D* mapChip2D{};
	ArrowMarker* marker_ = nullptr;

	bool isTutorial_ = false;

	int getCost_[43][52];

	std::vector<Sprite*> towerUISprites_;
	int32_t towerUIAnimationCount_ = 0;
	int32_t towerUIAnimationMax = 10;
	int32_t gameOverTimer_ = 0;
	int32_t towerBreakAnime_ = 0;
	int32_t towerBreakAnimeTimer_ = 0;

	bool poseBreak = false;
};

