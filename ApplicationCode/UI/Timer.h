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
    void Initialize(const int32_t maxTime);
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();
    /// <summary>
    /// 時計開放フラグをセット
    /// </summary>
    /// <param name="isOpen">時計開放フラグ</param>
    void SetIsWatchOpen(bool isOpen) { isWatchOpen_ = isOpen; }

    /// <summary>
    /// タイマースタート
    /// </summary>
    /// <param name="isTimerStart"></param>
    void SetIsTimerStart(bool isTimerStart) { isTimerStart_ = isTimerStart; }
    /// <summary>
    /// 現在のタイムの割合を取得
    /// </summary>
    int32_t GetTimeRange() { return nowTime_ / maxTime_; }

private: //メンバ関数
    /// <summary>
    /// 時間から回転角を求める
    /// </summary>
    void RotCulc();

private: //静的メンバ変数
    //アニメーションタイマー
    int32_t animationTime = 6;

private: //メンバ変数
    //現在時間
    int32_t nowTime_;
    //最大時間
    int32_t maxTime_;
    //時計
    std::unique_ptr<Sprite> watch_[7];
    //長針
    std::unique_ptr<Sprite> bigHand_;
    //長針回転
    float bigHandRot_;
    //時計アニメーション数
    int32_t watchAnimeCount_;
    //時計開放フラグ
    bool isWatchOpen_;
    //タイマースタートフラグ
    bool isTimerStart_;
    //時計開閉アニメーションタイマー
    int32_t animationTimer_;
};