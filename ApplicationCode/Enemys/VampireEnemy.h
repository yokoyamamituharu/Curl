#pragma once
#include"BaseEnemy.h"
#include<memory>
#include<list>
class VampireEnemy: public BaseEnemy
{
private:
	
	
	
	

public:
	~VampireEnemy();//�폜
	static std::unique_ptr<VampireEnemy> UniqueCreate();//�쐬

	void Update();// �X�V

	void Draw();//�`��

private: //�萔
	//�O�����A�j���[�V�����摜
	static const int32_t frontAnimationCount = 6;
	//�������A�j���[�V�����摜
	static const int32_t besideAnimationCount = 4;
	//�������A�j���[�V�����摜
	static const int32_t backAnimationCount = 6;

	int useAnimation = 0;
};

