#pragma once
#include "Sprite.h"

class ImageManager final
{
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& obj) = delete;
	ImageManager& operator=(const ImageManager& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ImageManager* GetIns();

public: //�摜��
	enum class ImageName {
		solidTexNumber = 1,
		liquidNumber,
		gasTexNumber,
		bgTexNumber,
		towerNumber,
		playerTexNumber,
		enemyindividual,
		enemyLiquid,
		enemyGas,
		heatWaveNumber,
		coldWaveNumber,
		playerHeatTexNumber,
		bloodGaugeNumber,
		ultGaugeNumber,
		overheatNumber,
		vampire_front,
		vampire_beside,
		vampire_back,
		basilisk_front,
		basilisk_beside,
		basilisk_back,
		rabbit_front,
		rabbit_beside,
		rabbit_back,
		GameUI_01,
		GameUI_02,
		GameUI_03,
		TowerUI,
		playerHp,
		TitleLog,
		ManualButton,
		StartButton,
		Pause,
		TitleBack,
		title,
		Clear,
		ClearBack,
		Back,
		Manual,
		gameOver,
		gameOverBack,
		stageSelect,
		stageSelectWindow,
		play,
		tutorial,
		wolfForwardWalk,
		wolfBackwardWalk,
		watch,
		watch_BigHand,
		reticle,
		particleCircle,
		guideArrow,
		messageWindow,
		mapChipTest,
		mapChipTest2,
		mapChipTest3,
		droppedLiquid,
		towerBreak
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

private:
	int mapChip = (int)ImageName::mapChipTest;
};

