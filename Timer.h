#pragma once
#include "Sprite.h"

class Timer
{
public: //メンバ関数
	Timer() = default;
	~Timer() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private: //メンバ変数
	//現在時間
	int32_t nowTime_;
	//最大時間
	int32_t maxTime_;
	//時計画像
	std::unique_ptr<Sprite> watch_;
	//長針画像
	std::unique_ptr<Sprite> bigHand_;
	//短針画像
	std::unique_ptr<Sprite> littleHand_;
};

