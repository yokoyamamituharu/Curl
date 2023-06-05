#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy : public BaseEnemy
{

private:


public:
	~BasiliskEnemy();
	static std::unique_ptr<BasiliskEnemy> UniqueCreate();

	void Update();

	void Draw();

private: //�萔
	//�O�����A�j���[�V������
	static const int32_t frontAnimationCount = 6;
	//�������A�j���[�V������
	static const int32_t besideAnimationCount = 2;
	//�������A�j���[�V������
	static const int32_t backAnimationCount = 6;

private: //�����o�ϐ�

	bool moveFlag{};
	float moveAngle = 1.f;
};

