#pragma once
#include "Sprite.h"
#include "Vector2.h"

class Collision2d final
{
private:
	Collision2d() = default;
	~Collision2d() = default;
	Collision2d(const Collision2d& obj) = delete;
	Collision2d& operator=(const Collision2d& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾�p�֐�
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Collision2d* GetIns();

public: //�����o�֐�
	/// <summary>
	/// �~�Ɖ~�̓����蔻��
	/// </summary>
	/// <param name="obj1">���肵�����X�v���C�g1</param>
	/// <param name="obj2">���肵�����X�v���C�g2</param>
	/// <param name="radius1">���肵�����X�v���C�g���a1</param>
	/// <param name="radius2">���肵�����X�v���C�g���a2</param>
	/// <returns>�������Ă��邩�ǂ���</returns>
	bool CircleAndCircle(Sprite* obj1, Sprite* obj2, float radius1, float radius2);
	/// <summary>
	/// �~�Ɖ~�̓����蔻��
	/// </summary>
	/// <param name="pos1">���肵�����X�v���C�g���W1</param>
	/// <param name="pos2">���肵�����X�v���C�g���W2</param>
	/// <param name="radius1">���肵�����X�v���C�g���a1</param>
	/// <param name="radius2">���肵�����X�v���C�g���a2</param>
	/// <returns>�������Ă��邩�ǂ���</returns>
	bool CircleAndCircle(Vector2 pos1, Vector2 pos2, float radius1, float radius2);
};

