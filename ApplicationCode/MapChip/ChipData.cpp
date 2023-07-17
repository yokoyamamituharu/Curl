#include "ChipData.h"


ChipData* ChipData::Create(int i, int j, const MapInfo name)
{
	ChipData* instance = new ChipData();
	instance->Ins(i,j, name);
	return instance;
}

void ChipData::Ins(int i, int j, const MapInfo name)
{
	
	chipNumber = (int)name + (int)ImageManager::ImageName::mapChipTest;
	Mapping(i, j);
	sprite_ = Sprite::Create(UINT(chipNumber), pos_, {1,1,1,1}, { 0.5,0.5 });
}

void ChipData::Mapping(int i, int j)
{
	pos_.x = (float)(i * size_.size()) + 32.f;
	pos_.y = (float)(j * size_.size()) + 32.f;
}

void ChipData::Draw()
{
	sprite_->Draw();
}

void ChipData::Delete()
{
	delete sprite_;
}

