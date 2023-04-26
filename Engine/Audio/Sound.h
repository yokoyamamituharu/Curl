#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <map>
#include <vector>
#include <string>

/// <summary>
/// �I�[�f�B�I�R�[���o�b�N
/// </summary>
class XSound2VoiceCallback : public IXAudio2VoiceCallback
{
public:
	// �{�C�X�����p�X�̊J�n��
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	// �{�C�X�����p�X�̏I����
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	// �o�b�t�@�X�g���[���̍Đ����I��������
	STDMETHOD_(void, OnStreamEnd) (THIS) {};
	// �o�b�t�@�̎g�p�J�n��
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
	// �o�b�t�@�̖����ɒB������
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
		// �o�b�t�@���������
		delete[] pBufferContext;
	};
	// �Đ������[�v�ʒu�ɒB������
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	// �{�C�X�̎��s�G���[��
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

/// <summary>
/// �I�[�f�B�I
/// </summary>
class Sound
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: // �T�u�N���X
	// �`�����N�w�b�_
	struct Chunk
	{
		char	id[4]; // �`�����N����ID
		int32_t		size;  // �`�����N�T�C�Y
	};

	// RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		Chunk	chunk;   // "RIFF"
		char	type[4]; // "WAVE"
	};

	// FMT�`�����N
	struct FormatChunk
	{
		Chunk		chunk; // "fmt "
		WAVEFORMAT	fmt;   // �g�`�t�H�[�}�b�g
	};

	struct SoundData {
		IXAudio2SourceVoice* sound;
		Chunk data;
		std::string fileName;
		char* pBuffer;
		bool isPlay;
	};

public: // �����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize();

	/// <summary>
	/// BGM���Đ�
	/// </summary>
	/// <param name="soundData">�Đ����������f�[�^</param>
	/// <param name="isRoop">���[�v�t���O</param>
	/// <param name="volume">bgm�Đ�</param>
	void PlaySoundData(const SoundData& soundData, bool isRoop, float volume);

	/// <summary>
	/// BGM���~
	/// </summary>
	/// <param name="soundData">��~���������f�[�^</param>
	/// <param name="isPause">�ꎞ��~�t���O</param>
	void StopSoundData(const SoundData& soundData, bool isPause);

	/// <summary>
	/// ���f�[�^�ǂݍ���
	/// </summary>
	/// <param name="fileName">�ǂݍ��މ��f�[�^�t�@�C��</param>
	/// <param name="soundData">�������މ��f�[�^�\����</param>
	void LoadSound(const std::string& fileName, SoundData& soundData);

private: // �����o�ϐ�
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	XSound2VoiceCallback voiceCallback;
};

