#include "Timer.h"
#include "ImageManager.h"
#include "Vector2.h"

void Timer::Initialize(const int32_t maxTime)
{
	const Vector2 anchorPoint = { 0.5f, 0.5f };
	const float watchXSize = 64.0f;
	const float watchYSize = 128.0f;

	nowTime_ = 0;
	maxTime_ = maxTime;
	for (int32_t i = 0; i < 7; i++) {
		watch_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::watch, { 640.0f, 8.0f });
		watch_[i]->SetUi(true);
		watch_[i]->SetAnchorPoint(anchorPoint);
		watch_[i]->SetTextureRect({ watchXSize * (float)i, 0.0f }, { watchXSize, watchYSize });
		watch_[i]->SetSize({ watchXSize, watchYSize });
	}
	bigHand_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::watch_BigHand, { 640.0f, 39.5f });
	bigHand_->SetUi(true);
	bigHand_->SetAnchorPoint({ anchorPoint.x, 1.0f });

	bigHandRot_ = 0.0f;
}

void Timer::Update()
{
	if (isTimerStart_) {
		if (++nowTime_ < maxTime_) {
			RotCulc();
			bigHand_->SetRotation(bigHandRot_);
		}
		else {
			nowTime_ = maxTime_;
		}
	}

	if (++animationTimer_ > animationTime) {
		animationTimer_ = 0;
		if (isWatchOpen_) {
			watchAnimeCount_++;
		}
		else {
			watchAnimeCount_--;
		}
	}

	if (watchAnimeCount_ >= 7) {
		watchAnimeCount_ = 6;
	}
	else if (watchAnimeCount_ <= 0) {
		watchAnimeCount_ = 0;
	}
}

void Timer::Draw()
{

	watch_[watchAnimeCount_]->Draw();
	if (watchAnimeCount_ >= 3) {
		bigHand_->Draw();
	}
	
}

void Timer::RotCulc()
{
	//Œ»İŠÔ‚ğ0~1‚Ì”ÍˆÍ‚Éû‚ß‚é
	float timeRate = (float)nowTime_ /(float)maxTime_;

	//‰ñ“]Šp‚ğ‹‚ß‚é
	bigHandRot_ = 360.0f * timeRate;
}
