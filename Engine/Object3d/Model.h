#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <unordered_map>

class Model
{
private: // �G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;
		float pad1;
		XMFLOAT3 diffuse;
		float pad2;
		XMFLOAT3 specular;
		float alpha;
	};
	//�}�e���A��
	struct Material
	{
		std::string name;
		XMFLOAT3 ambient;
		XMFLOAT3 diffuse;
		XMFLOAT3 specular;
		float alpha;
		std::string textureFilename;

		Material() {
			ambient = { 0.3f, 0.3f, 0.3f };
			diffuse = { 0.0f, 0.0f, 0.0f };
			specular = { 0.0f, 0.0f, 0.0f };
			alpha = 1.0f;
		}
	};

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;

private: //�����o�ϐ�
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;
	//�}�e���A��
	Material material;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB1;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// ����
	/// </summary>
	static Model* CreateModel(const std::string& modelname, bool isSmoothing = false);

	/// <summary>
	/// �}�`���f������
	/// </summary>
	/// <param name="vertices_">���_</param>
	/// <param name="indices_">���_�C���f�b�N�X</param>
	/// <param name="textureName">�e�N�X�`����</param>
	/// <returns></returns>
	static Model* CreateShapeModel(const std::vector<VertexPosNormalUv>& vertices_, const std::vector<unsigned short> indices_, const std::string& textureName);

public: //�����o�֐�
	/// <summary>
	/// �}�e���A���̎擾
	/// </summary>
	/// <returns></returns>
	Material GetMaterial() { return material; }

	/// <summary>
	/// �A���r�G���g���Z�b�g
	/// </summary>
	/// <param name="ambient"></param>
	void SetAmbient(const XMFLOAT3& ambient) { material.ambient = ambient; }

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �}�e���A���̓ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// ���f��������
	/// </summary>
	void InitializeModel(const std::string& modelname, bool isSmoothing);

	/// <summary>
	/// �}�`���f��������
	/// </summary>
	/// <param name="vertices_">���_�f�[�^</param>
	/// <param name="indices_">���_�C���f�b�N�X</param>
	/// <param name="textureName">�e�N�X�`����</param>
	void InitializeShapesModel(const std::vector<VertexPosNormalUv>& vertices_, const std::vector<unsigned short> indices_, const std::string& textureName);

	/// <summary>
	/// �G�b�W�������p�f�[�^��ǉ�
	/// </summary>
	/// <param name="indexPosition">���W�C���f�b�N�X</param>
	/// <param name="indexVertex">���_�C���f�b�N�X</param>
	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	/// <summary>
	/// �������������_�@���̌v�Z
	/// </summary>
	void CalculateSmoothedVertexNormals();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Material material);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private: //�����o�֐�
	/// <summary>
	/// �g���q�𕪗�����
	/// </summary>
	/// <param name="filePath">�g���q�𕪗��������t�@�C���p�X</param>
	/// <returns>�g���q</returns>
	std::wstring SeparatedExtension(const std::wstring& filePath);

};