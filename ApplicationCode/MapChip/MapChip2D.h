#pragma once
#include"ChipData.h"
class MapChip2D
{


private:
	
public:
	static MapChip2D* Create();
	void MapChipData();
	void Ins();
	void Draw();

	void Delete();
	ChipData* GetChipData(int i, int j) {return chipData[i][j];}

private:
	std::array<int, 10> sizeX_;
	std::array<int, 10> sizeY_;
	ChipData* chipData[10][10]{};

	int mapChipData[10][10];

};

