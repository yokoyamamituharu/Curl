#pragma once
#include "BaseEnemy.h"
class RabbitEnemy :public BaseEnemy
{
private:


public:
	~RabbitEnemy();
	static std::unique_ptr<RabbitEnemy> UniqueCreate();

	void Update();

	int BloodHit(int num);

	void Draw();

private: //�萔
	//�O�����A�j���[�V�����摜
	static const int32_t frontAnimationCount = 3;
	//�������A�j���[�V�����摜
	static const int32_t besideAnimationCount = 3;
	//�������A�j���[�V�����摜
	static const int32_t backAnimationCount = 3;
};

