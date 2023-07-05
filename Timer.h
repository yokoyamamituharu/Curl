#pragma once
#include "Sprite.h"

class Timer
{
public: //�����o�֐�
	Timer() = default;
	~Timer() = default;
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�ϐ�
	//���ݎ���
	int32_t nowTime_;
	//�ő厞��
	int32_t maxTime_;
	//���v�摜
	std::unique_ptr<Sprite> watch_;
	//���j�摜
	std::unique_ptr<Sprite> bigHand_;
	//�Z�j�摜
	std::unique_ptr<Sprite> littleHand_;
};

