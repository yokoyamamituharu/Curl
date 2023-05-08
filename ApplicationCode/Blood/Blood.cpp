#include "Blood.h"
#include "ImageManager.h"

Blood* Blood::Create(DirectX::XMFLOAT2 position, STATE state)
{
    Blood* instance = new Blood();
    instance->position = position;
    instance->sprite[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
    instance->sprite[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
    instance->sprite[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
    instance->state = state;
    return instance;
}

void Blood::Update()
{
    //XVˆ—
    sprite[state]->SetPosition(position);
}

void Blood::Rising()
{
    if (state >= gas)return;
    state++;
}

void Blood::Decrease()
{
    if (state <= solid)return;
    state--;
}


void Blood::Draw()
{
    sprite[state]->Draw();
}