#include "ArrowMarker.h"
#include "SafeDelete.h"
#include "ImageManager.h"
#include "WinApp.h"

ArrowMarker::ArrowMarker()
{
}

ArrowMarker::~ArrowMarker()
{
	safe_delete(sprite_);
}

ArrowMarker* ArrowMarker::Create(Vector2 pos)
{
	ArrowMarker* instance = new ArrowMarker();
	instance->Initialize(pos);
	return instance;
}

void ArrowMarker::Initialize(Vector2 pos)
{
	this->pos_ = pos;
	sprite_ = Sprite::Create((UINT)ImageManager::ImageName::guideArrow, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	sprite_->SetSize({ 56,87 });
	sprite_->SetUi(true);
}

void ArrowMarker::Update(Vector2 camera)
{
	isMarker_ = false;
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;
	Vector2 markerPos = {};
	float markerAngle = {};
	float radiusSize = 32;

	if (pos_.x < camera.x - radiusSize)
	{
		isMarker_ = true;
		isLeft = true;
	}
	if (pos_.x > WinApp::window_width + camera.x + radiusSize)
	{
		isMarker_ = true;
		isRight = true;
	}

	if (pos_.y < camera.y - radiusSize)
	{
		isMarker_ = true;
		isUp = true;
	}
	if (pos_.y > WinApp::window_height + camera.y + radiusSize)
	{
		isMarker_ = true;
		isDown = true;
	}

	//画面内に座標がある場合早期リターン
	if (!isMarker_)return;
#pragma endregion 描画がスクリーンの外で行われているかの判定

#pragma region マーカーを出すための処理

	if (isLeft || isRight) {
		if (isUp == false && isDown == false) {
			markerPos.y = pos_.y - camera.y;
			if (markerPos.y < 32) {
				markerPos.y = 32;
			}
			if (markerPos.y > WinApp::window_height - 32) {
				markerPos.y = WinApp::window_height - 32;
			}
		}
	}

	if (isUp || isDown) {
		if (isLeft == false && isRight == false) {
			markerPos.x = pos_.x - camera.x;
			if (markerPos.x < 32) {
				markerPos.x = 32;
			}
			if (markerPos.x > WinApp::window_width - radiusSize - 96) {
				markerPos.x = WinApp::window_width - radiusSize - 96;
			}
		}
	}

	if (isLeft) {
		markerPos.x = radiusSize;
	}
	else if (isRight) {
		markerPos.x = WinApp::window_width - radiusSize - 96;
	}

	if (isUp) {
		markerPos.y = radiusSize;
	}
	else if (isDown) {
		markerPos.y = WinApp::window_height - radiusSize;
	}

	//画面の中央座標
	Vector2 screenCenter = { camera.x + WinApp::window_width / 2,camera.y + WinApp::window_height };
	//自分の位置から画面の中心へのベクトル
	Vector2 vec = screenCenter - pos_;
	vec.normalize();
	// atan2 を使用して角度を取得
	markerAngle = atan2f(vec.x, vec.y);
	//角度をラジアンから度へ変換
	markerAngle = markerAngle * 180.0f / 3.14f;
	//補正値を足す
	float PI = -1;
	markerAngle *= PI;

	sprite_->SetPosition(markerPos);
	sprite_->SetRotation(markerAngle);
}

void ArrowMarker::Draw()
{
	if (isMarker_ && !isInvisible_) {
		sprite_->Draw();
	}
}
