#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

class BaseLight {
private: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BaseLight() = default;
	virtual ~BaseLight() {}

public: //�T�u�N���X
	struct ConstBufferData {
		XMVECTOR lightVec; //���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightColor; //���C�g�̐F
		XMFLOAT3 lightPos;
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static BaseLight* Create() {};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �萔�o�b�t�@�փf�[�^�]��
	/// </summary>
	virtual void TransferConstBuffer() = 0;

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightDir">���C�g����</param>
	 virtual void SetLightDir(const XMVECTOR& lightDir) = 0;

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	virtual void SetLightColor(const XMFLOAT3& lightColor) = 0;

	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="light"></param>
	virtual void SetLightPos(XMFLOAT3 pos) = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rootParameter">�w�胋�[�g�p�����[�^</param>
	virtual void Draw(UINT rootParameter) = 0;

protected: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

protected: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���C�g��������
	XMVECTOR lightDir = { 1, 0, 0, 0 };
	//���C�g�F
	XMFLOAT3 lightColor = { 1, 1, 1 };
	//���C�g���W	
	XMFLOAT3 lightPos = { 0, 0, 0 };
	//�_�[�e�B�t���O
	bool isDirty = false;
};