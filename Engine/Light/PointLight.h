#pragma once
#include <DirectXMath.h>

class PointLight
{
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X
	struct ConstBufferData {
		XMFLOAT3 lightPos;
		float pad1;
		XMFLOAT3 lightColor;
		float pad2;
		XMFLOAT3 lightAtten;
		unsigned int isActive;
	};

public: //�����o�֐�
	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="lightPos">���C�g���W</param>
	inline void SetLightPos(const XMFLOAT3& lightPos) { this->lightPos = lightPos; }

	/// <summary>
	/// ���C�g���W���擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	inline const XMFLOAT3& GetLightPos() { return lightPos; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	inline void SetLightColor(const XMFLOAT3& lightColor) { this->lightColor = lightColor; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	inline const XMFLOAT3& GetLightColor() { return lightColor; }

	/// <summary>
	/// ���C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="lightAtten">���C�g���������W��</param>
	inline void SetLightAtten(const XMFLOAT3& lightAtten) { this->lightAtten = lightAtten; }

	/// <summary>
	/// ���C�g���������W�����擾
	/// </summary>
	/// <returns>���C�g���������W��</returns>
	inline const XMFLOAT3& GetLightAtten() { return lightAtten; }

	/// <summary>
	/// �_�����L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	inline void SetActive(bool isActive) { this->isActive = isActive; }

	/// <summary>
	/// �_�����L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	inline bool GetIsActive() { return isActive; }

private: //�����o�ϐ�
	//���C�g���W
	XMFLOAT3 lightPos = { 0, 0, 0 };
	//���C�g�F
	XMFLOAT3 lightColor = { 1, 1, 1 };
	//���C�g���������W��
	XMFLOAT3 lightAtten = { 1.0f, 1.0f, 1.0f };
	//�L�����t���O
	bool isActive = false;
};