#pragma once
#include"ChipData.h"
class MapChip2D
{


private:
	enum MapInfo
	{
		//�}�b�v�̎�ނ��������Ă������O�͉�
		NONE,
		ONES
	};
public:
	static MapChip2D* Create();
	void MapChipData();
	void Ins();
	ChipData* GetChipData(int i, int j) {return chipData[i][j];}

private:
	std::array<int, 10> sizeX_;
	std::array<int, 10> sizeY_;
	ChipData* chipData[10][10]{};

	int mapChipData[10][10];

};

