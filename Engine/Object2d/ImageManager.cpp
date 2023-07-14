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
	Sprite::LoadTexture(int32_t(ImageName::ultGaugeNumber), L"Engine/Resources/Images/bloodGauge.png");
	Sprite::LoadTexture(int32_t(ImageName::overheatNumber), L"Engine/Resources/Images/overheat.png");
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
	Sprite::LoadTexture(int32_t(ImageName::GameUI_01), L"Engine/Resources/Images/UIBack.png");
	Sprite::LoadTexture(int32_t(ImageName::GameUI_02), L"Engine/Resources/Images/thermometer.png");
	Sprite::LoadTexture(int32_t(ImageName::GameUI_03), L"Engine/Resources/Images/temperatureValue.png");
	Sprite::LoadTexture(int32_t(ImageName::playerHp), L"Engine/Resources/Images/hp.png");
	Sprite::LoadTexture(int32_t(ImageName::TitleLog), L"Engine/Resources/Images/TitleLog.png");
	Sprite::LoadTexture(int32_t(ImageName::ManualButton), L"Engine/Resources/Images/ManualButton.png");
	Sprite::LoadTexture(int32_t(ImageName::StartButton), L"Engine/Resources/Images/StartButton.png");
	Sprite::LoadTexture(int32_t(ImageName::Pause), L"Engine/Resources/Images/pause.png");
	Sprite::LoadTexture(int32_t(ImageName::TitleBack), L"Engine/Resources/Images/titleBack.png");
	Sprite::LoadTexture(int32_t(ImageName::Clear), L"Engine/Resources/Images/clear.png");
	Sprite::LoadTexture(int32_t(ImageName::Back), L"Engine/Resources/Images/Back.png");
	Sprite::LoadTexture(int32_t(ImageName::Manual), L"Engine/Resources/Images/Manual.png");
	Sprite::LoadTexture(int32_t(ImageName::gameOver), L"Engine/Resources/Images/GameOver.png");
	Sprite::LoadTexture(int32_t(ImageName::wolfForwardWalk), L"Engine/Resources/Images/wolfForwardWalk.png");
	Sprite::LoadTexture(int32_t(ImageName::wolfBackwardWalk), L"Engine/Resources/Images/wolfBackwardWalk.png");
	Sprite::LoadTexture(int32_t(ImageName::watch), L"Engine/Resources/Images/Watch.png");
	Sprite::LoadTexture(int32_t(ImageName::watch_BigHand), L"Engine/Resources/Images/Watch_BigHand.png");
	Sprite::LoadTexture(int32_t(ImageName::reticle), L"Engine/Resources/Images/reticle.png");
	Sprite::LoadTexture(int32_t(ImageName::particleCircle), L"Engine/Resources/Images/particleCircle.png");
	Sprite::LoadTexture(int32_t(ImageName::guideArrow), L"Engine/Resources/Images/guideArrow.png");
	
}
