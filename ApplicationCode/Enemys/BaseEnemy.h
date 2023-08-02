#pragma once
#include<array>
#include<DirectXMath.h>
#include <vector>
#include"Vector2.h"
#include"Sprite.h"
#include "ImageManager.h"
#include"..\AStar.h"

class BaseEnemy
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;
	

public:

	enum EnemyType
	{
		vampire = 7,//��
		basilisk,//�t��
		rabbit,//�C��
	};
	enum BloodState //���̃^�C�v
	{
		NONE_1,
		solid_1,
		liquid_1,
		gas_1
	};

	enum AnimationType 
	{
		front,
		rightSide,
		back,
		ReftSide,
	};
public:
	virtual ~BaseEnemy() {};//�f���[�g

	XMFLOAT2 Getpos() { return pos; }//���W�擾

	void SetMoveAddLength(float moveAddLength_) { this->moveAddLength = moveAddLength_; }//���Z�������
	float GetMoveAddLength() { return moveAddLength; }//���Z�����擾

	void SetMoveLength(float moveLength_) { this->moveLength = moveLength_; }//�������
	float GetMoveLength() { return moveLength; }//�����擾

	void SetBloodType(int bloodTipe_) { this->BloodType = bloodTipe_; }//���̃^�C�v���
	int GetBloodType() { return BloodType; }//���̃^�C�v�擾

	void SetHitBloodType(int hitBloodType_) { this->hitBloodType = hitBloodType_; }//���Ȍ��̃^�C�v���
	int GetHitBloodType() { return hitBloodType; }//���Ȍ��̃^�C�v�擾

	void SetAnBloodType(int anBloodType_) { this->anBloodType = anBloodType_; }//���ӂȌ��̃^�C�v���
	int GetAnBloodType() { return anBloodType; }//���ӂȌ��̃^�C�v�K��

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }//���̓����蔻����
	bool GetBloodHitFlag() { return bloodHitFlag; }//���̓����蔻��擾

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }//����Ă���Ԃ̓����蔻����
	bool GetTowerHitFlag() { return towerHitFlag; }//����Ă���Ԃ̓����蔻��擾

	void SetDead(bool dead_) { this->dead = dead_; }//���S�t���O���
	bool GetDead() { return dead; }//���S�t���O�擾

	void SetMovePoint(XMFLOAT2 pos) { this->movePoint = pos; }//����Ă���ԍ��W���
	XMFLOAT2 GetMovePoint() { return movePoint; }//����Ă���ԍ��W�擾

	void OnCollision() { dead = true; }

	virtual	void Update() = 0;//�X�V

	//void Create(int type);

	virtual void Draw(bool makerFlag = true) = 0;//�`��

	void WorldMarker(XMFLOAT2 camera);

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

	XMFLOAT2 pos{};//���W

	float angle{};//�p�x
	float moveLength{};//����
	float moveAddLength = 1;//���Z����

	int BloodType{};//���̃^�C�v
	int hitBloodType{};//���̌��̃^�C�v
	int anBloodType{};//���ӂ̌��̃^�C�v

	bool bloodHitFlag{};//���Ƃ̓����蔻��t���O
	bool towerHitFlag{};//�ԂƂ̓����蔻��t���O
	bool dead{};//

	bool minWidthFlag{};
	bool minHeightFlag{};
	bool maxWidthFlag{};
	bool maxHeightFlag{};


	
	std::list<Cell>route;
	std::array<float, 360> maxAngle;//�p�x�ő�l
	std::array<float, 0> minAngle;//�p�x�ŏ��l

	//��ʊO�ɂ���Ƃ��ɉ�ʓ��ɏo���}�[�J�[
	Sprite* markerSprite_ = nullptr;
	XMVECTOR markerAdd{};
	float markerLength = 1;
	XMFLOAT2 markerPos_{};
	float markerAngle{};
	bool isMarker_ = false;
	bool isRight_ = false;
	bool isLeft_ = false;
	bool isUp_ = false;
	bool isDown_ = false;

	//�ړ�����W
	XMFLOAT2 movePoint = { 640.f,360.f };
	//�A�j���[�V�����^�C�}�[
	int32_t animationTimer_ = 0;
	//�O�����A�j���[�V�����J�E���^�[
	int32_t frontAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t besideAnimationCounter_ = 0;
	//�������A�j���[�V�����J�E���^�[
	int32_t backAnimationCounter_ = 0;
};

