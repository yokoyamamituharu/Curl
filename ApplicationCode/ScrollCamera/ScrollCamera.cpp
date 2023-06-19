#include "ScrollCamera.h"
#include "KeyInput.h"
#include "Sprite.h"

ScrollCamera::~ScrollCamera()
{
	Sprite::SetCamera(nullptr);
}

ScrollCamera* ScrollCamera::Create()
{
	ScrollCamera* instance = new ScrollCamera();
	instance->pos = { 0,0 };
	return instance;
}

void ScrollCamera::Update(Vector2  adulationTarge)
{
	float cameraSpeed = 5.0f;
	if (KeyInput::GetIns()->PushKey(DIK_I)) {
		pos.y -= cameraSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_K)) {
		pos.y += cameraSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_L)) {
		pos.x += cameraSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_J)) {
		pos.x -= cameraSpeed;
	}

	//この値を超えたらスクロールをさせる
	Vector2 minPos = { WinApp::window_width / 2, WinApp::window_height / 2 };
	//スクロールの終わりの座標
	Vector2 maxPos = { 2000,1000 };
	
	//スクロールの計算
	if (adulationTarge.x > minPos.x) {
		pos.x = adulationTarge.x - minPos.x;
	}
	if (adulationTarge.y > minPos.y) {
		pos.y = adulationTarge.y - minPos.y;
	}
	if (adulationTarge.x > maxPos.x) {
		pos.x = maxPos.x;
	}
	if (adulationTarge.y > maxPos.y) {
		pos.y = maxPos.y;
	}
}