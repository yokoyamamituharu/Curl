#include "Blood.h"
#include "ImageManager.h"

Blood::Blood()
{
}

Blood::~Blood()
{
    for (auto sprite : sprites) {
        delete sprite.second;
    }
    sprites.clear();
}

Blood* Blood::Create(DirectX::XMFLOAT2 position, STATE state)
{
    Blood* instance = new Blood();
    instance->position = position;
    instance->sprites[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
    instance->sprites[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
    instance->sprites[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
    instance->state = state;
    return instance;
}

void Blood::Update()
{
    //XVˆ—
    sprites[state]->SetPosition(position);
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
    sprites[state]->Draw();
}