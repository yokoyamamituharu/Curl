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
	Sprite::LoadTexture(int32_t(ImageName::bgTexNumber), L"Engine/Resources/Images/bg.png");
	Sprite::LoadTexture(int32_t(ImageName::towerNumber), L"Engine/Resources/Images/tower.png");

	Sprite::LoadTexture(int32_t(ImageName::enemyindividual), L"Engine/Resources/Images/enemy(1).png");
	Sprite::LoadTexture(int32_t(ImageName::enemyLiquid), L"Engine/Resources/Images/enemy(2).png");
	Sprite::LoadTexture(int32_t(ImageName::enemyGas), L"Engine/Resources/Images/enemy(3).png");
}
