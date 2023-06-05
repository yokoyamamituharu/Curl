#pragma once
#include<array>
#include<DirectXMath.h>
#include <vector>

#include"Sprite.h"
#include "ImageManager.h"

class BaseEnemy
{
private:
protected:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

	enum EnemyType
	{
		vampire = 7,//��
		basilisk,//�t��
		rabbit,//�C��
	};
	enum BloodState {
		NONE_1,
		solid_1,
		liquid_1,
		gas_1
	};
public:
	virtual ~BaseEnemy() {};

	XMFLOAT2 Getpos() { return pos; }

	void SetMoveAddLength(float moveAddLength_) { this->moveAddLength = moveAddLength_; }
	float GetMoveAddLength() { return moveAddLength; }

	void SetMoveLength(float moveLength_) { this->moveLength = moveLength_; }
	float GetMoveLength() { return moveLength; }

	void SetBloodType(int bloodTipe_) { this->BloodType = bloodTipe_; }
	int GetBloodType() { return BloodType; }

	void SetHitBloodType(int hitBloodType_) { this->hitBloodType = hitBloodType_; }
	int GetHitBloodType() { return hitBloodType; }

	void SetAnBloodType(int anBloodType_) { this->anBloodType = anBloodType_; }
	int GetAnBloodType() { return anBloodType; }

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }
	int GetBloodHitFlag() { return bloodHitFlag; }

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }
	int GetTowerHitFlag() { return towerHitFlag; }

	void SetDead(bool dead_) { this->dead = dead_; }
	bool GetDead() { return dead; }

	virtual	void Update() = 0;
	
	//void Create(int type);

	virtual void Draw() = 0;

protected: //�ÓI�����o�֐�

	/// <summary>
	/// �G�摜����
	/// </summary>
	/// <param name="imageName">�摜��</param>
	/// <param name="animationCount">�A�j���[�V������</param>
	/// <param name="enemyPos">�G���W</param>
	/// <returns>�A�j���[�V�����X�v���C�g</returns>
	static std::vector<Sprite*> SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& enemyPos);

protected: //�萔
	//�A�j���[�V��������
	static const int32_t animationTime = 10;

protected:
	std::vector<Sprite*> frontSprites_;
	std::vector<Sprite*> besideSprites_;
	std::vector<Sprite*> backSprites_;

	XMFLOAT2 pos{};

	float angle{};
	float moveLength{};
	float moveAddLength = 1;

	int BloodType{};
	int hitBloodType{};
	int anBloodType{};

	bool bloodHitFlag{};
	bool towerHitFlag{};
	bool dead{};

	std::array<float, 360> maxAngle;
	std::array<float, 0> minAngle;

	XMFLOAT2 centerPoint = {640.f,360.f};
	//�A�j���[�V�����^�C�}�[
	int32_t animationTimer_ = 0;
	//�O�����A�j���[�V�����J�E���^�[
	int32_t frontAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t besideAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t backAnimationCounter_ = 0;
};

