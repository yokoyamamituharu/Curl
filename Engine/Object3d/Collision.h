#pragma once
#include "Object3d.h"
#include "Vector3.h"
#include "DirectXMath.h"
#include"WinApp.h"
class Collision final
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	Collision() = default;
	~Collision() = default;
	Collision(const Collision& obj) = delete;
	Collision& operator=(const Collision& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾�p�֐�
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Collision* GetIns();

public: //�����o�֐�

	static bool HitCircle(XMFLOAT2 pos1, float radius1, XMFLOAT2 pos2, float radius2);

	static XMFLOAT2 HitCrossWindows(XMFLOAT2 enemyPos,int flag);
	
	static bool CrossLine(XMFLOAT2 pos1, XMFLOAT2 pos2, XMFLOAT2 pos3, XMFLOAT2 pos4);

	static XMFLOAT2 CrossLinePoint(XMFLOAT2 pos1, XMFLOAT2 pos2, XMFLOAT2 pos3, XMFLOAT2 pos4);
	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="object1">���肵�����I�u�W�F�N�g1</param>
	/// <param name="object2">���肵�����I�u�W�F�N�g2</param>
	/// <param name="objScale1">���肵�����I�u�W�F�N�g�̔��a1</param>
	/// <param name="objScale2">���肵�����I�u�W�F�N�g�̔��a2</param>
	/// <returns>��������</returns>
	bool OBJSphereCollision(Object3d* object1, Object3d* object2, float objScale1, float objScale2);

private: //�����o�ϐ�
	Vector3 object1Pos = { 0, 0, 0 };
	Vector3 object2Pos = { 0, 0, 0 };

	float objectPosTotal = 0;
	float objectScaleTotal = 0;
};

