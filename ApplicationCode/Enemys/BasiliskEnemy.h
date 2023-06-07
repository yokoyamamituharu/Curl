#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy : public BaseEnemy
{

private:
	
	
	
	

public:
	~BasiliskEnemy();//�폜
	static std::unique_ptr<BasiliskEnemy> UniqueCreate();//�쐬

	void Update();// �X�V

	void Draw();//�`��

private: //�萔
	//�O�����A�j���[�V������
	static const int32_t frontAnimationCount = 6;
	//�������A�j���[�V������
	static const int32_t besideAnimationCount = 2;
	//�������A�j���[�V������
	static const int32_t backAnimationCount = 6;

private: //�����o�ϐ�

	bool moveFlag{};//���E�ǂ����ɉ�邩�̃t���O
	float moveAngle = 1.f;//�A���O�����Z�l
};

