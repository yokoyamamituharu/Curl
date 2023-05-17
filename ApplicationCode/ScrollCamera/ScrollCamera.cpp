#include "ScrollCamera.h"
#include "KeyInput.h"
#include "Sprite.h"

ScrollCamera* ScrollCamera::Create()
{
    ScrollCamera* instance = new ScrollCamera();
    instance->pos = { 0,0 };
    return instance;
}

void ScrollCamera::Update()
{
    float cameraSpeed = 5.0f;
    //if (KeyInput::GetIns()->PushKey(DIK_UP)) {
    //    pos.y -= cameraSpeed;
    //}
    //if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
    //    pos.y += cameraSpeed;
    //}
    //if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
    //    pos.x += cameraSpeed;
    //}
    //if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
    //    pos.x -= cameraSpeed;
    //}
}

void ScrollCamera::Draw(Sprite* sprite)
{
    sprite->SetPosition(sprite->GetPosition() - pos);
    sprite->Draw();
    sprite->SetPosition(sprite->GetPosition() + pos);
}
