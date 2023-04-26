#include "Sound.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

bool Sound::Initialize() {
	HRESULT result;

	// XSound�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}

void Sound::PlaySoundData(const SoundData& soundData, bool isRoop, float volume)
{
	HRESULT result;

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)soundData.pBuffer;
	buf.pContext = soundData.pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = soundData.data.size;
	if (isRoop == true) {
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	soundData.sound->SetVolume(volume);

	// �g�`�f�[�^�̍Đ�
	if (!soundData.isPlay) {
		result = soundData.sound->SubmitSourceBuffer(&buf);
		result = soundData.sound->Start();
	}

}

void Sound::StopSoundData(const SoundData& soundData, bool isPause)
{
	HRESULT result;
	XAUDIO2_VOICE_STATE voiceState;
	soundData.sound->GetState(&voiceState);
	soundData.sound->Stop();
	if (!isPause) {
		result = soundData.sound->FlushSourceBuffers();
	}
}

void Sound::LoadSound(const std::string& fileName, SoundData& soundData)
{
	HRESULT result;
	// �t�@�C���X�g���[��
	std::ifstream file;
	// Wave�t�@�C�����J��
	file.open(fileName, std::ios_base::binary);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	// Format�`�����N�̓ǂݍ���
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	// Data�`�����N�̓ǂݍ���
	file.read((char*)&soundData.data, sizeof(soundData.data));

	// Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
	soundData.pBuffer = new char[soundData.data.size];
	file.read(soundData.pBuffer, soundData.data.size);

	// Wave�t�@�C�������
	file.close();

	WAVEFORMATEX wfex{};
	// �g�`�t�H�[�}�b�g�̐ݒ�
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	result = xAudio2->CreateSourceVoice(&soundData.sound, &wfex, 0, 2.0f, &voiceCallback);
}