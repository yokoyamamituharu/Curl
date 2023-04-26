#pragma once
#include "FBXModel.h"
#include "Camera.h"
#include "FbxLoader.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FBXObject3d
{
protected: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�萔
    //�{�[���̍ő吔
	static const int32_t MAX_BONES = 32;

public: //�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};

	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public: //�ÓI�����o�֐�
	//�Z�b�^�[
	static void SetDevice(ID3D12Device* device) { FBXObject3d::device = device; }
	static void SetCamera(Camera* camera) { FBXObject3d::camera = camera; }
	static void CreateGraphicsPipeline();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model">���f��</param>
	void SetModel(FBXModel* model) { this->model = model; }

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
    /// ���W�̎擾
    /// </summary>
    /// <returns>���W</returns>
	const XMFLOAT3& GetPosition() { return position; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	/// <summary>
	/// �傫���̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetScale() { return scale; }

	/// <summary>
	/// �傫���̐ݒ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	/// <summary>
	/// ��]�p�̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetRotation() { return rotation; }

	/// <summary>
	/// ��]�p�̐ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	/// <summary>
	/// �A�j���[�V�������Đ�
	/// </summary>
	/// <param name="isLoop">���[�v�Đ��t���O</param>
	/// <param name="animeNo">�A�j���[�V�����ԍ�</param>
	void PlayAnimation(bool isLoop = true, int32_t animeNo = 0);

	/// <summary>
	/// �A�j���[�V�������~
	/// </summary>
	void StopAnimation();

	/// <summary>
	/// �Đ������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsAnimation() { return isPlay; }

	/// <summary>
	/// ���[���h�ϊ��s��̎擾
	/// </summary>
	/// <returns>���[���h�ϊ��s��</returns>
	const XMMATRIX& GetMatWorld() { return matWorld; }

protected: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBufferTransform;
	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1, 1, 1 };
	//X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0, 0, 0 };
	//���[�J�����W
	XMFLOAT3 position = { 0, 0, 0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	FBXModel* model = nullptr;
	//�萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBufferSkin;
	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ������ǂ����̃t���O
	bool isPlay = false;
	//�A�j���[�V���������[�v�����邩�ǂ����̃t���O
	bool isLoop = false;

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
};

