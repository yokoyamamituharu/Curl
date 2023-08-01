#pragma once
#include "BaseEnemy.h"
class RabbitEnemy :public BaseEnemy
{
private:
	
	
	
	

public:
	~RabbitEnemy();//�폜
	static std::unique_ptr<RabbitEnemy> UniqueCreate(Cell cell);//�쐬

	void Update();// �X�V

	int BloodHit(int num);

	void Draw(bool isInvisible = true);//�`��

private: //�萔
	//�O�����A�j���[�V�����摜
	static const int32_t frontAnimationCount = 3;
	//�������A�j���[�V�����摜
	static const int32_t besideAnimationCount = 3;
	//�������A�j���[�V�����摜
	static const int32_t backAnimationCount = 3;

	int useAnimation = 0;

	Cell dPos_ = { 0,0 };
	Cell gorl = { 0,0 };

	int chipSize = 64;
};

