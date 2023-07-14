#include "ScrollCamera.h"
#include "KeyInput.h"
#include "Sprite.h"

const Vector2 ScrollCamera::minPos = { WinApp::window_width / 2, WinApp::window_height / 2 };
const Vector2 ScrollCamera::maxPos = { minPos.x + 2000,minPos.y + 2000 };

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
	//float cameraSpeed = 5.0f;
	//if (KeyInput::GetIns()->PushKey(DIK_I)) {
	//	pos.y -= cameraSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_K)) {
	//	pos.y += cameraSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_L)) {
	//	pos.x += cameraSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_J)) {
	//	pos.x -= cameraSpeed;
	//}

	//スクロールの計算

	//pos = minPos;
	if (adulationTarge.x > minPos.x) {
		pos.x = adulationTarge.x - minPos.x;
	}
	if (adulationTarge.y > minPos.y) {
		pos.y = adulationTarge.y - minPos.y;
	}
	if (pos.x > maxPos.x - minPos.x) {
		pos.x = maxPos.x - minPos.x;
	}
	if (pos.y > maxPos.y - minPos.y) {
		pos.y = maxPos.y - minPos.y;
	}
}

Vector2 ScrollCamera::GetMinScreenEdge()
{
	Vector2 win = { WinApp::window_width / 2, WinApp::window_height / 2 };
	return Vector2(minPos - win);
}

Vector2 ScrollCamera::GetMaxScreenEdge()
{
	Vector2 win = { WinApp::window_width / 2, WinApp::window_height / 2 };
	return Vector2(maxPos + win);
}
