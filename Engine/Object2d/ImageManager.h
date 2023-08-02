#pragma once
#include "Sprite.h"

class ImageManager final
{
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& obj) = delete;
	ImageManager& operator=(const ImageManager& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static ImageManager* GetIns();

public: //画像名
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

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

private:
	int mapChip = (int)ImageName::mapChipTest;
};

