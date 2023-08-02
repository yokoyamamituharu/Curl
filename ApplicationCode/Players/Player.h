#pragma once
#include "Sprite.h"
#include "Blood.h"
#include "list"
#include "Vector2.h"
#include "ScrollCamera.h"

class KeyInputHandler;
class Player
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	enum class State
	{
		none,
		idle,
		heat
	};

	enum class AnimationType
	{
		none,
		front,
		RightSide,
		back,
		LeftSide,
	};

	Player() = default;

	~Player();

	/// <summary>
	/// �v���C���[�̐���
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rote"></param>
	/// <param name="hp"></param>
	/// <param name="maxBlood"></param>
	/// <returns></returns>
	static Player* Create(Vector2 pos, float rote, int hp, int maxBlood[], int speed[]);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera"></param>
	void Update(ScrollCamera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="scroll"></param>
	void Draw(ScrollCamera* scroll);

	/// <summary>
	/// �v���C���[���w�肵���ʒu�ɐi�߂�
	/// </summary>
	/// <param name="vec"></param>
	void AddPlayerVector(Vector2 vec);

	/// <summary>
	/// ���W���Z�b�g����
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector2 position) { position_ = position; }

	/// <summary>
	/// �v���C���[�̈ړ����x�̎擾
	/// </summary>
	/// <returns></returns>
	float GetSpeed() { return speed_; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	Vector2 GetPosition() { return position_; }

	/// <summary>
	/// �v���C���[��HP�̎擾
	/// </summary>
	int GetPlayerHp() { return playerHp_; }

	/// <summary>
	/// �v���C���[��HP���Z�b�g����
	/// </summary>
	/// <param name="playerHp"></param>
	void SetPlayerHp(int playerHp) { this->playerHp_ = playerHp; }

	/// <summary>
	/// �����擾����
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<Blood>>& GetBloods() { return bloods_; }

	/// <summary>
	/// �g���錌�̎c�ʂ��擾
	/// </summary>
	/// <returns></returns>
	int GetBloodGauge() { return bloodGauge_; }

	/// <summary>
	/// ���̍ő�l���擾
	/// </summary>
	/// <returns></returns>
	int GetMaxBloodGauge() { return maxBlood_; }

	/// <summary>
	/// �E���g�Q�[�W�̒l���擾
	/// </summary>
	float GetUltGaugeM(int level) { return ultGauge[level]; }

	float GetUltGauge() { return ultGauge[ultLevel_]; }

	/// <summary>
	/// �E���g�ő�l
	/// </summary>
	float GetUltMaxGauge() { return ultMaxGauge; }

	/// <summary>
	/// �E���g���
	/// </summary>
	/// <returns></returns>
	bool GetUltState() const { return ultState; }

	/// <summary>
	/// ���̔���
	/// </summary>
	/// <param name="camera"></param>
	void Shot(ScrollCamera* camera, Vector2 pos = { -100,-100 });

	int GetUltLevel() { return ultLevel_; }

	void SetOldPos() { position_ = oldPlayerPos; }

private:
	/// <summary>
	/// �A�j���[�V�����摜�̐���
	/// </summary>
	/// <param name="imageName"></param>
	/// <param name="animationCount"></param>
	/// <param name="enemyPos"></param>
	/// <returns></returns>
	static std::vector<Sprite*> SpritesCreateP(int imageName, int32_t animationCount, Vector2& pos);

	/// <summary>
	/// �ړ�
	/// </summary>
	/// <param name="camera"></param>
	/// <returns>�ړ����������s�������ǂ���</returns>
	bool Move(ScrollCamera* camera);

	/// <summary>
	/// �M�g�A���g�̍X�V
	/// </summary>
	void Wave();

	static  int32_t frontAnimationCount;
	static  int32_t backAnimationCount;
	static  int32_t animationTime;

private:
	std::vector<Sprite*> frontSprites_;
	std::vector<Sprite*> backSprites_;
	Vector2 position_{};
	int state_ = (int)State::none;
	KeyInputHandler* handler_ = nullptr;
	const float initSpeed_ = 2.0f;
	float speed_ = initSpeed_;
	int playerHp_ = 10;
	int maxBlood_ = 0;
	int bloodGauge_ = 0;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;

	Sprite* heatWave_ = nullptr;
	Sprite* coldWave_ = nullptr;

	bool isRecall_ = false;
	// �M�g
	bool isHeatWave_ = false;
	float heatExtend_ = 0;
	float heatAlpha_ = 1;
	// ���g
	bool isColdWave_ = false;
	float coldExtend_ = 0;
	float coldAlpha_ = 1;

	// �E���g���
	bool ultState = false;			// �Q�[�W���
	float ultGauge[6] = {};				// �Q�[�W�l
	const float ultMaxGauge = 10;	// �Q�[�W�ő�l
	//const float maxUltDiray = 60;	// �Q�[�W�����鑬�x
	//float ultDiray = maxUltDiray;
	int ultLevel_ = 0;				//����E���g��ԂɂȂ�����	
	const int maxUltChargeDray_ = 180;	
	const int maxUltCharge_ = 100;
	int ultChargeDray_ = maxUltChargeDray_;
	//int ultCharge_ = maxUltCharge_;	//�E���g���x���������Ԃ̏ꍇ�A����������Ȃ��ƃ`���[�W���؂�Ăǂ�ǂ񃌃x����������
	int ultSpeed_[6] = {};
	int ultMaxBlood_[6] = {};


	bool isMove_ = false;
	int useAnimation_ = 0;
	int useDirectionSide_ = 0;
	//�A�j���[�V�����^�C�}�[
	int32_t animationTimer_ = 0;
	//�O�����A�j���[�V�����J�E���^�[
	int32_t frontAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t backAnimationCounter_ = 0;

	Vector2 oldPlayerPos{};
};