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
		front,
		rightSide,
		back,
		ReftSide,
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
	static Player* Create(Vector2 pos, float rote, int hp, int maxBlood);

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
	/// �X�v���C�g�̎擾
	/// </summary>
	Sprite* GetSprite() { return sprites_[state_]; }

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

private:
	/// <summary>
	/// �A�j���[�V�����摜�̐���
	/// </summary>
	/// <param name="imageName"></param>
	/// <param name="animationCount"></param>
	/// <param name="enemyPos"></param>
	/// <returns></returns>
	static std::vector<Sprite*> SpritesCreateP(int imageName, int32_t animationCount, Vector2& enemyPos);

	/// <summary>
	/// ���̔���
	/// </summary>
	/// <param name="camera"></param>
	void Shot(ScrollCamera* camera);

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move(ScrollCamera* camera);

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
	std::map<int, Sprite*> sprites_;
	Vector2 position_{};
	float heat_ = 0;
	int maxHeatDiray_ = 0;
	int heatDiray_ = maxHeatDiray_;
	int state_ = (int)State::none;
	KeyInputHandler* handler_ = nullptr;
	float speed_ = 4.0f;
	int playerHp_ = 10;
	int maxBlood_ = 0;
	int bloodGauge_ = 0;
	std::list<std::unique_ptr<Blood>>bloods_;
	const int maxShotDiray_ = 10;
	int shotDiray_ = maxShotDiray_;

	Sprite* heatWave_ = nullptr;
	Sprite* coldWave_ = nullptr;

	bool isHeatWave = false;
	float heatExtend = 0;
	float heatAlpha = 1;

	bool isColdWave = false;
	float coldExtend = 0;
	float coldAlpha = 1;
	bool isRecall_ = false;

	float angle = 0;
	int useAnimation = 0;
	//�A�j���[�V�����^�C�}�[
	int32_t animationTimer_ = 0;
	//�O�����A�j���[�V�����J�E���^�[
	int32_t frontAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t backAnimationCounter_ = 0;
};