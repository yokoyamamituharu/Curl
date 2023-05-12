#pragma once
#include "Sprite.h"
#include "Vector2.h"

class Tower
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Tower() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Tower() = default;

public: //�����o�֐�
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="hp">����HP</param>
	void Initialize(int32_t hp);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	/// <summary>
	/// HP�擾
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHP() { return hp_; }

	/// <summary>
	/// �^���[�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�^���[�I�u�W�F�N�g</returns>
	Sprite* GetTower() { return tower_.get(); }

private: //�����o�ϐ�
	//HP
	int32_t hp_;
	//���W
	Vector2 pos_;
	//�^���[�I�u�W�F�N�g
	std::unique_ptr<Sprite> tower_;

};

