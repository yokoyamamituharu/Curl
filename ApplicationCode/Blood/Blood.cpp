#include "Blood.h"
#include "ImageManager.h"

Blood::Blood()
{
}

Blood::~Blood()
{
    for (auto sprite : sprites_) {
        delete sprite.second;
    }
    sprites_.clear();
}

Blood* Blood::Create(DirectX::XMFLOAT2 position, STATE state)
{
    Blood* instance = new Blood();
    instance->position_ = position;
    instance->sprites_[solid] = Sprite::Create(UINT(ImageManager::ImageName::solidTexNumber), position);
    instance->sprites_[liquid] = Sprite::Create(UINT(ImageManager::ImageName::liquidNumber), position);
    instance->sprites_[gas] = Sprite::Create(UINT(ImageManager::ImageName::gasTexNumber), position);
    instance->state_ = state;
    return instance;
}

void Blood::Update()
{
    //XVˆ—
    sprites_[state_]->SetPosition(position_);
}

void Blood::Rising()
{
    if (state_ >= gas)return;
    state_++;
}

void Blood::Decrease()
{
    if (state_ <= solid)return;
    state_--;
}


void Blood::Draw()
{
    sprites_[state_]->Draw();
}