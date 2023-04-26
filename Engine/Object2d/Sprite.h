#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <memory>

class Sprite
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X

    // ���_�f�[�^
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat;   // �R�c�ϊ��s��
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static bool StaticInitialize(ID3D12Device* device, int32_t window_width, int32_t window_height);
	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�摜�t�@�C����</param>
	/// <returns></returns>
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);
	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g1</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();
	/// <summary>
	/// �X�v���C�g����
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g</param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	/// <returns></returns>
	static Sprite* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	/// <summary>
	/// �X�v���C�g����(unique_ptr)
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="anchorpoint"><�A���J�[�|�C���g/param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	/// <returns></returns>
	static std::unique_ptr<Sprite> UniquePtrCreate(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

protected: //�ÓI�����o�ϐ�
	//�e�N�X�`���̍ő喇��
	static const int32_t srvCount = 512;
	//���_��
	static const int32_t vertNum = 4;
	//�f�o�C�X
	static ID3D12Device* device;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	//�R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	//�ˉe�s��
	static XMMATRIX matProjection;
	//�f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[srvCount];

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g</param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns>�ʒu</returns>
	const XMFLOAT2& GetPosition() { return position; }
	/// <summary>
	/// �傫���擾
	/// </summary>
	/// <returns>�傫��</returns>
	const XMFLOAT2& GetSize() { return size; }
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	bool Initialize();
	/// <summary>
	/// �p�x�̐ݒ�
	/// </summary>
	/// <param name="rotation">�p�x</param>
	void SetRotation(float rotation);
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT2 position);
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(XMFLOAT2 size);
	/// <summary>
	/// �A���J�[�|�C���g�̐ݒ�
	/// </summary>
	/// <param name="anchorpoint"></param>
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	/// <summary>
	/// ���E���]�̐ݒ�
	/// </summary>
	/// <param name="isFlipX">���E���]</param>
	void SetIsFlipX(bool isFlipX);
	/// <summary>
	/// �㉺���]�̐ݒ�
	/// </summary>
	/// <param name="isFlipY">�㉺���]</param>
	void SetIsFlipY(bool isFlipY);
	/// <summary>
	/// �X�v���C�g�F�̐ݒ�
	/// </summary>
	/// <param name="color">�X�v���C�g�F</param>
	void SetColor(XMFLOAT3 color) {
		this->color.x = color.x;
		this->color.y = color.y;
		this->color.z = color.z;
	}
	/// <summary>
	/// �A���t�@�l�̐ݒ�
	/// </summary>
	/// <param name="alpha"></param>
	void SetAlpha(float alpha) { this->alpha = alpha; }
	/// <summary>
	/// �摜���̕␳�ݒ�
	/// </summary>
	/// <param name="isLeftSizeCorrection"></param>
	void SetLeftSizeCorrection(bool isLeftSizeCorrection) { this->isLeftSizeCorrection = isLeftSizeCorrection; }
	/// <summary>
	/// �摜�E�̕␳�ݒ�
	/// </summary>
	/// <param name="isRightSizeCorrection"></param>
	void SetRightSizeCorrection(bool isRightSizeCorrection) { this->isRightSizeCorrection = isRightSizeCorrection; }
	/// <summary>
	/// �e�N�X�`���͈͐ݒ�
	/// </summary>
	/// <param name="texBase">�e�N�X�`��������W</param>
	/// <param name="texSize">�e�N�X�`���T�C�Y</param>
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

protected: //�����o�ϐ�
	//���_�o�b�t�@;
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�萔�o�b�t�@;
	ComPtr<ID3D12Resource> constBuff;
	// Z�����̉�]�p
	float rotation = 0.0f;
	// ���W
	XMFLOAT2 position = {};
	// ���[���h�s��
	XMMATRIX matWorld;
	// �F(RGBA)
	XMFLOAT4 color = { 1, 1, 1, 1 };
	//�A���t�@�l
	float alpha = 1.0f;
	// �e�N�X�`���ԍ�
	UINT texNumber = 0;
	// �傫��
	XMFLOAT2 size = { 100, 100 };
	//���T�C�Y�␳�t���O
	bool isLeftSizeCorrection = true;
	//�E�T�C�Y�␳�t���O
	bool isRightSizeCorrection = true;
	// �A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0.5f, 0.5f };
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// �e�N�X�`��������W
	XMFLOAT2 texBase = { 0, 0 };
	// �e�N�X�`���T�C�Y
	XMFLOAT2 texSize = { 100, 100 };

private: //�����o�֐�
	/// <summary>
	/// ���_�f�[�^�]��
	/// </summary>
	void TransferVertices();
};

