#pragma once
#include <DirectXMath.h>

class CircleShadow {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct ConstBufferData {
		XMVECTOR dir;
		XMFLOAT3 casterPos;
		float distanceCasterLight;
		XMFLOAT3 atten;
		float pad3;
		XMFLOAT2 cosAngle;
		unsigned int isActive;
		float pad4;
	};

public: //�����o�֐�
	/// <summary>
	/// �������Z�b�g
	/// </summary>
	/// <param name="dir">����</param>
	void SetDir(const XMVECTOR& dir) { this->dir = DirectX::XMVector3Normalize(dir); }

	/// <summary>
	/// �L���X�^�[���W���Z�b�g
	/// </summary>
	/// <param name="casterPos">��Q��</param>
	void SetCasterPos(const XMFLOAT3& casterPos) { this->casterPos = casterPos; }

	/// <summary>
	/// �L���X�^�[�ƃ��C�g�̋���
	/// </summary>
	/// <param name="distanceCasterLight"></param>
	void SetDistanceCasterLight(float distanceCasterLight) { this->distanceCasterLight = distanceCasterLight; }

	/// <summary>
	/// ���������W�����Z�b�g
	/// </summary>
	/// <param name="atten">���������W��</param>
	void SetAtten(const XMFLOAT3& atten) { this->atten = atten; }

	/// <summary>
	/// �����p�x���Z�b�g
	/// </summary>
	/// <param name="cosAngle">�����p�x</param>
	void SetAngle(const XMFLOAT2& cosAngle) {
		this->cosAngle.x = cosf(DirectX::XMConvertToRadians(cosAngle.x));
		this->cosAngle.y = cosf(DirectX::XMConvertToRadians(cosAngle.y));
	}

	/// <summary>
	/// �ۉe�L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	void SetIsActive(bool isActive) { this->isActive = isActive; }

	/// <summary>
	/// �L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	bool GetIsActive() { return isActive; }

	/// <summary>
	/// �������擾
	/// </summary>
	/// <returns>����</returns>
	const XMVECTOR& GetDir() { return dir; }

	/// <summary>
	/// �L���X�^�[���W���擾
	/// </summary>
	/// <returns>�L���X�^�[���W</returns>
	const XMFLOAT3& GetCasterPos() { return casterPos; }

	/// <summary>
	/// �L���X�^�[�ƃ��C�g�̋������擾
	/// </summary>
	/// <returns>�L���X�^�[�ƃ��C�g�̋���</returns>
	float GetDistanceCasterLight() { return distanceCasterLight; }

	/// <summary>
	/// ���������W�����擾
	/// </summary>
	/// <returns>���������W��</returns>
	const XMFLOAT3& GetAtten() { return atten; }

	/// <summary>
	/// �����p�x���擾
	/// </summary>
	/// <returns>�����p�x</returns>
	const XMFLOAT2& GetAngle() { return cosAngle; }

private: //�����o�ϐ�
	XMVECTOR dir = { 1, 0, 0, 0 };
	float distanceCasterLight = 100.0f;
	XMFLOAT3 casterPos = { 0, 0, 0 };
	XMFLOAT3 atten = { 0.5f, 0.6f, 0.0f };
	XMFLOAT2 cosAngle = { 0.2f, 0.5f };
	bool isActive = false;
};