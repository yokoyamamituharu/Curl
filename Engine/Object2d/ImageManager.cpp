#include "ImageManager.h"

ImageManager* ImageManager::GetIns()
{
	static ImageManager instance;
	return &instance;
}

void ImageManager::Initialize() {
	Sprite::LoadTexture(int32_t(ImageName::solidTexNumber),L"Engine/Resources/Images/solid.png");
	Sprite::LoadTexture(int32_t(ImageName::liquidNumber), L"Engine/Resources/Images/liquid.png");
	Sprite::LoadTexture(int32_t(ImageName::gasTexNumber), L"Engine/Resources/Images/gas.png");
	Sprite::LoadTexture(int32_t(ImageName::playerTexNumber), L"Engine/Resources/Images/player.png");
	Sprite::LoadTexture(int32_t(ImageName::playerHeatTexNumber), L"Engine/Resources/Images/playerHeat.png");
	Sprite::LoadTexture(int32_t(ImageName::bgTexNumber), L"Engine/Resources/Images/bg.png");
	Sprite::LoadTexture(int32_t(ImageName::towerNumber), L"Engine/Resources/Images/tower.png");
	Sprite::LoadTexture(int32_t(ImageName::heatWaveNumber), L"Engine/Resources/Images/heatWave.png");
	Sprite::LoadTexture(int32_t(ImageName::coldWaveNumber), L"Engine/Resources/Images/coldWave.png");
	Sprite::LoadTexture(int32_t(ImageName::bloodGaugeNumber), L"Engine/Resources/Images/bloodGauge.png");
	Sprite::LoadTexture(int32_t(ImageName::enemyindividual), L"Engine/Resources/Images/enemy(1).png");
	Sprite::LoadTexture(int32_t(ImageName::enemyLiquid), L"Engine/Resources/Images/enemy(2).png");
	Sprite::LoadTexture(int32_t(ImageName::enemyGas), L"Engine/Resources/Images/enemy(3).png");
	Sprite::LoadTexture(int32_t(ImageName::vampire_front), L"Engine/Resources/Images/vampire_front.png");
	Sprite::LoadTexture(int32_t(ImageName::vampire_beside), L"Engine/Resources/Images/vampire_beside.png");
	Sprite::LoadTexture(int32_t(ImageName::vampire_back), L"Engine/Resources/Images/vampire_back.png");
	Sprite::LoadTexture(int32_t(ImageName::basilisk_front), L"Engine/Resources/Images/basilisk_front.png");
	Sprite::LoadTexture(int32_t(ImageName::basilisk_beside), L"Engine/Resources/Images/basilisk_beside.png");
	Sprite::LoadTexture(int32_t(ImageName::basilisk_back), L"Engine/Resources/Images/basilisk_back.png");
	Sprite::LoadTexture(int32_t(ImageName::rabbit_front), L"Engine/Resources/Images/rabbit_front.png");
	Sprite::LoadTexture(int32_t(ImageName::rabbit_beside), L"Engine/Resources/Images/rabbit_beside.png");
	Sprite::LoadTexture(int32_t(ImageName::rabbit_back), L"Engine/Resources/Images/rabbit_back.png");
	Sprite::LoadTexture(int32_t(ImageName::TitleLog), L"Engine/Resources/Images/TitleLog.png");
}
