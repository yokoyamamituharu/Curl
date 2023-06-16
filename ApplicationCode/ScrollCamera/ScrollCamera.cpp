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
    //pos = adulationTarge;
}