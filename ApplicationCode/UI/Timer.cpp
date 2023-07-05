#include "Timer.h"
#include "ImageManager.h"
#include "Vector2.h"

void Timer::Initialize(const int32_t maxTime)
{
	const Vector2 anchorPoint = { 0.5f, 0.5f };

	nowTime_ = 0;
	maxTime_ = maxTime;
	watch_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::watch, { 0.0f, 0.0f });
	watch_->SetUi(true);
	watch_->SetAnchorPoint(anchorPoint);
	bigHand_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::watch_BigHand, { 640.0f, 360.0f });
	bigHand_->SetUi(true);
	bigHand_->SetAnchorPoint(anchorPoint);
	littleHand_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::watch_LittleHand, { 0.0f, 0.0f });
	littleHand_->SetUi(true);
	littleHand_->SetAnchorPoint(anchorPoint);

	bigHandRot_ = 0.0f;
	littleHandRot_ = 0.0f;
}

void Timer::Update()
{
	if (++nowTime_ < maxTime_) {
		RotCulc();
		bigHand_->SetRotation(bigHandRot_);
	}
}

void Timer::Draw()
{
	watch_->Draw();
	bigHand_->Draw();
	littleHand_->Draw();
}

void Timer::RotCulc()
{
	//Œ»İŠÔ‚ğ0~1‚Ì”ÍˆÍ‚Éû‚ß‚é
	float timeRate = (float)nowTime_ /(float)maxTime_;

	//‰ñ“]Šp‚ğ‹‚ß‚é
	bigHandRot_ = 360.0f * timeRate;
}
