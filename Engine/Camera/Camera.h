#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
private: //�G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public: //�T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �J����������
	/// </summary>
	/// <param name="window_width">��ʉ���</param>
	/// <param name="window_height">��ʏc��</param>
	static void InitializeCamera(int32_t window_width, int32_t window_height);

	/// <summary>
	/// �r���[�s����X�V
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// ���[���h�s��̍X�V
	/// </summary>
	static void UpdateWorldMatrix();

	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// ����x�N�g���̃Z�b�g
	/// </summary>
	/// <param name="up">����x�N�g��</param>
	static void SetUp(XMFLOAT3 up);

	/// <summary>
	/// ���[���h�s��̃Z�b�g
	/// </summary>
	/// <param name="matWorld">���[���h�s��</param>
	static void SetMatWorld(XMMATRIX matWorld);

	/// <summary>
	/// �x�N�g���ɂ��ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	static void CameraMoveVector(XMFLOAT3 move);
	static void CameraMoveEyeVector(XMFLOAT3 move);
	static void CameraMoveTargetVector(XMFLOAT3 move);

	/// <summary>
	/// �r���[�s��̎擾
	/// </summary>
	/// <returns>�r���[�s��</returns>
	static const XMMATRIX& GetMatView() { return matView; }

	/// <summary>
	/// �ˉe�s��̎擾
	/// </summary>
	/// <returns>�ˉe�s��</returns>
	static const XMMATRIX& GetMatProjection() { return matProjection; }

	/// <summary>
	/// �r���{�[�h�s����|����
	/// </summary>
	/// <returns>�r���{�[�h�s��</returns>
	static const XMMATRIX& GetMatBillboard() { return matBillboard; }

	/// <summary>
	/// Y���r���{�[�h�s����|����
	/// </summary>
	/// <returns>Y���r���{�[�h�s��</returns>
	static const XMMATRIX& GetMatBillboardY() { return matBillboardY; }

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	static const XMMATRIX& GetMatWorld() { return matWorld; }

	/// <summary>
	/// �r���[�|�[�g�s��̎擾
	/// </summary>
	/// <returns>�r���[�|�[�g�s��</returns>
	static const XMMATRIX& GetMatViewPort() { return matViewPort; }

private: //�ÓI�����o�ϐ�
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	//���[���h�s��
	static XMMATRIX matWorld;
	//�r���{�[�h�s��
	static XMMATRIX matBillboard;
	//Y���r���{�[�h�s��
	static XMMATRIX matBillboardY;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	//�r���[�|�[�g�s��
	static XMMATRIX matViewPort;
	//���[���h�s��ݒ�̃t���O
	static bool isMatWorldCalc;
};

