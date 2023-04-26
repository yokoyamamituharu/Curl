#pragma once

#include <DirectXMath.h>

class SpotLight {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X
	struct ConstBufferData {
		XMVECTOR lightVec;
		XMFLOAT3 lightPos;
		float pad1;
		XMFLOAT3 lightColor;
		float pad2;
		XMFLOAT3 lightAtten;
		float pad3;
		XMFLOAT2 lightCosAngle;
		unsigned int isActive;
		float pad4;
	};

public: //�����o�֐�

	/// <summary>
	/// ���C�g�������擾
	/// </summary>
	/// <returns>���C�g����</returns>
	const XMVECTOR& GetLightVec() { return lightVec; }

	/// <summary>
	/// ���C�g���W���擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	const XMFLOAT3& GetLightPos() { return lightPos; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	const XMFLOAT3& GetLightColor() { return lightColor; }

	/// <summary>
	/// ���C�g���������W�����擾
	/// </summary>
	/// <returns>���C�g���������W��</returns>
	const XMFLOAT3& GetLightAtten() { return lightAtten; }

	/// <summary>
	/// ���C�g�����p�x(�J�n�p�x�A�I���p�x)
	/// </summary>
	/// <returns>���C�g�����p�x</returns>
	const XMFLOAT2& GetLightCosAngle() { return lightCosAngle; }

	/// <summary>
	/// �L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	bool GetIsActive() { return isActive; }

	/// <summary>
	/// �X�|�b�g���C�g�L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	void SetIsActive(bool isActive) { this->isActive = isActive; }

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightVec">���C�g����</param>
	void SetLightVec(const XMVECTOR& lightVec) { this->lightVec = DirectX::XMVector3Normalize(lightVec); }

	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="lightPos">���C�g���W</param>
	void SetLightPos(const XMFLOAT3& lightPos) { this->lightPos = lightPos; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	void SetLightColor(const XMFLOAT3& lightColor) { this->lightColor = lightColor; }

	/// <summary>
	/// ���C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="lightAtten">���C�g���������W��</param>
	void SetLightAtten(const XMFLOAT3& lightAtten) { this->lightAtten = lightAtten; }

	/// <summary>
	/// ���C�g�����p�x���Z�b�g
	/// </summary>
	/// <param name="lightCosAngle">���C�g�����p�x</param>
	void SetLightCosAngle(const XMFLOAT2& lightCosAngle) { 
		this->lightCosAngle.x = cosf(DirectX::XMConvertToRadians(lightCosAngle.x));
		this->lightCosAngle.y = cosf(DirectX::XMConvertToRadians(lightCosAngle.y));
	}

private: //�����o�ϐ�
	XMVECTOR lightVec = { 1, 0, 0, 0 };
	XMFLOAT3 lightPos = { 0, 0, 0 };
	XMFLOAT3 lightColor = { 1, 1, 1 };
	XMFLOAT3 lightAtten = { 1.0f, 1.0f, 1.0f };
	XMFLOAT2 lightCosAngle = { 0.5f, 0.2f };
	bool isActive = false;
};