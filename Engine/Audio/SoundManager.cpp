#include "SoundManager.h"

SoundManager* SoundManager::GetIns()
{
	static SoundManager instance;
	return &instance;
}

void SoundManager::Initialize(Sound* sound)
{
	this->sound_ = sound;
}

void SoundManager::PlayBGM(const BGMKey bgmKey, const bool isRoop, const float volume)
{
	if (bgmMap_[bgmKey].data.size <= 0) {
		LoadBGM(bgmMap_[bgmKey].fileName, bgmKey);
	}
	sound_->PlaySoundData(bgmMap_[bgmKey], isRoop, volume);
	bgmMap_[bgmKey].isPlay = true;
}

void SoundManager::PlaySE(const SEKey seKey, const float volume)
{
	//XAUDIO2_VOICE_STATE voiceState;
	//seMap[seKey].sound->GetState(&voiceState);

	//if (voiceState.BuffersQueued <= 0) {
	//	seMap[seKey].isPlay = false;
	//	StopSE(seKey);
	//}

	//test

	seMap_[seKey].pBuffer = nullptr;
	seMap_[seKey].sound = nullptr;
	seMap_[seKey].isPlay = false;
	seMap_[seKey].data.size = 0;

	if (seMap_[seKey].data.size <= 0) {
		LoadSE(seMap_[seKey].fileName, seKey);
	}
	sound_->PlaySoundData(seMap_[seKey], false, volume);
	seMap_[seKey].isPlay = true;
}

void SoundManager::StopBGM(const BGMKey bgmKey, const bool isPause)
{
	sound_->StopSoundData(bgmMap_[bgmKey], isPause);
	bgmMap_[bgmKey].isPlay = false;
	if (!isPause) {
		bgmMap_[bgmKey].data.size = 0;
	}
}

void SoundManager::StopSE(const SEKey seKey, const bool isPause)
{
	sound_->StopSoundData(seMap_[seKey], isPause);
	seMap_[seKey].isPlay = false;
	if (!isPause) {
		seMap_[seKey].data.size = 0;
	}
}

void SoundManager::LoadBGM(const std::string& fileName, BGMKey bgmKey)
{
	if (bgmMap_[bgmKey].fileName.size() <= 0) {
		bgmMap_[bgmKey].fileName = fileName;
	}
	sound_->LoadSound(fileName, bgmMap_[bgmKey]);
}

void SoundManager::LoadSE(const std::string& fileName, SEKey seKey)
{
	if (seMap_[seKey].fileName.size() <= 0) {
		seMap_[seKey].fileName = fileName;
	}
	sound_->LoadSound(fileName, seMap_[seKey]);
}
