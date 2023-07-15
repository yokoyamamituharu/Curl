#include "ChipData.h"


ChipData* ChipData::Create(int i, int j, int number)
{
	ChipData* instance = new ChipData();
	return instance;
}

void ChipData::Ins(int i, int j, int number)
{
	chipNumber = number;
	Mapping(i, j);
}

void ChipData::Mapping(int i, int j)
{
	pos_.x = (float)(i * size_.size());
	pos_.y = (float)(j * size_.size());
}