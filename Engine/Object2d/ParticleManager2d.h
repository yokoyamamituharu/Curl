#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include <forward_list>

class ParticleManager2d
{
public: //�\����
	struct Particle2d {
		//���W
		Vector2 pos_;
		//���x�x�N�g��
		Vector2 velocity_;
		//�����x
		Vector2 accel_;
		//�F
		Vector3 color_;
		//�A���t�@�l
		float alpha_;
		//�����p�����[�^
		Vector3 start_Color_;
		float start_Size_;
		float start_Rot_;
		float start_Alpha_;
		//�ŏI�p�����[�^
		Vector3 end_Color_;
		float end_Size_;
		float end_Rot_;
		float end_Alpha_;
		//���݃t���[��
		int32_t nowFrame_;
		//�ŏI�t���[��
		int32_t endFrame_;
		//�p�[�e�B�N���摜
		std::unique_ptr<Sprite> particle_;
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	//static ParticleManager2d* Create();
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	//static std::unique_ptr<ParticleManager2d> UniquePtrCreate();
	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	//static std::unique_ptr<Particle2d> ParticleCreate();

public: //�����o�֐�
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N���ǉ�
	/// </summary>
	/// <param name="particle">�p�[�e�B�N��</param>
	void Add(const Particle2d& particle);

private: //�����o�ϐ�
	//�p�[�e�B�N�����X�g
	std::forward_list<Particle2d> particleList_;
};