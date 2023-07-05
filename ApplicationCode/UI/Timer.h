#pragma once
#include "Sprite.h"

class Timer
{
public: //ƒƒ“ƒoŠÖ”
    Timer() = default;
    ~Timer() = default;
    /// <summary>
    /// ‰Šú‰»
    /// </summary>
    void Initialize(const int32_t maxTime);
    /// <summary>
    /// XVˆ—
    /// </summary>
    void Update();
    /// <summary>
    /// •`‰æˆ—
    /// </summary>
    void Draw();

private: //ƒƒ“ƒoŠÖ”
    /// <summary>
    /// ŠÔ‚©‚ç‰ñ“]Šp‚ğ‹‚ß‚é
    /// </summary>
    void RotCulc();

private: //ƒƒ“ƒo•Ï”
    //Œ»İŠÔ
    int32_t nowTime_;
    //Å‘åŠÔ
    int32_t maxTime_;
    //Œv
    std::unique_ptr<Sprite> watch_;
    //’·j
    std::unique_ptr<Sprite> bigHand_;
    //’Zj
    std::unique_ptr<Sprite> littleHand_;
    //’·j‰ñ“]
    float bigHandRot_;
    //’Zj‰ñ“]
    float littleHandRot_;
};