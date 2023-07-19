#include "BaseEnemy.h"
#include "SafeDelete.h"
#include"Collision.h"

std::vector<Sprite*> BaseEnemy::SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& enemyPos)
{
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, enemyPos));
		sprites[i]->SetAnchorPoint({ 0.5f, 0.5f });
		sprites[i]->SetPosition(enemyPos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 64.0f * (float)i;
		sprites[i]->SetSize({ 64.0f, 64.0f });
		sprites[i]->SetTextureRect(texBase, { 64.0f, 64.0f });
	}
	return sprites;
}

void BaseEnemy::WorldMarker(XMFLOAT2 camera)
{

#pragma region 敵の描画がスクリーンの外で行われているかの判定
	//スクリーンの最小値　- 32
	//スクリーンの最大値　+ 32
	//上の二つの中にプレイヤーがいるかの判定
	isMarker_ = false;
	isLeft_ = false;
	isRight_ = false;
	isUp_ = false;
	isDown_ = false;
	//敵の画像の半分のサイズ
	float radiusSize = 32;

	if (pos.x < camera.x - radiusSize)
	{
		isMarker_ = true;
		isLeft_ = true;
	}
	if (pos.x > WinApp::window_width + camera.x + radiusSize)
	{
		isMarker_ = true;
		isRight_ = true;
	}

	if (pos.y < camera.y - radiusSize)
	{
		isMarker_ = true;
		isUp_ = true;
	}
	if (pos.y > WinApp::window_height + camera.y + radiusSize)
	{
		isMarker_ = true;
		isDown_ = true;
	}
#pragma endregion 描画がスクリーンの外で行われているかの判定

#pragma region マーカーを出すための処理

	if (isLeft_ || isRight_) {
		if (isUp_ == false && isDown_ == false) {
			markerPos_.y = pos.y - camera.y;
			if (markerPos_.y < 32) {
				markerPos_.y = 32;
			}
			if (markerPos_.y > WinApp::window_height - 32) {
				markerPos_.y = WinApp::window_height - 32;
			}
		}
	}

	if (isUp_ || isDown_) {
		if (isLeft_ == false && isRight_ == false) {
			markerPos_.x = pos.x - camera.x;
			if (markerPos_.x < 32) {
				markerPos_.x = 32;
			}
			if (markerPos_.x > WinApp::window_width - radiusSize - 96) {
				markerPos_.x = WinApp::window_width - radiusSize - 96;
			}
		}
	}

	if (isLeft_) {
		markerPos_.x = radiusSize;
	}
	else if (isRight_) {
		markerPos_.x = WinApp::window_width - radiusSize - 96;
	}

	if (isUp_) {
		markerPos_.y = radiusSize;
	}
	else if (isDown_) {
		markerPos_.y = WinApp::window_height - radiusSize;
	}

	//画面の中央座標
	Vector2 screenCenter = { camera.x + WinApp::window_width / 2,camera.y + WinApp::window_height };
	//自分の位置から画面の中心へのベクトル
	Vector2 vec = screenCenter - pos;
	vec.normalize();
	// atan2 を使用して角度を取得
	markerAngle = atan2f(vec.x, vec.y);
	//角度をラジアンから度へ変換
	markerAngle = markerAngle * 180.0f / 3.14f;
	//補正値を足す
	float PI = -1;
	markerAngle *= PI;

#pragma endregion マーカーを出すための処理

	}