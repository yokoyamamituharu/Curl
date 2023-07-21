#include "MapChip2D.h"

MapChip2D* MapChip2D::Create()
{
	MapChip2D* instance = new MapChip2D();
	return instance;
}

void MapChip2D::MapChipData()
{
	//ステージ構成
	//[][]←これの中身は最大数に応じて変える
	//最大数の設定はsizeX_とsizeY_で設定
	int temp[10][10] =
	{
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,1,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,}
	};
	//ステージデータ代入
	for (int i = 0; i < sizeX_.size(); i++)
	{
		for (int j = 0; j < sizeY_.size(); j++)
		{
			mapChipData[i][j] = temp[i][j];
		}
	}
}

void MapChip2D::Ins()
{
	//ステージ作成
	MapChipData();

	for (int i = 0; i < sizeX_.size(); i++)
	{
		for (int j = 0; j < sizeY_.size(); j++)
		{
			//チップそれぞれの番号によって作成
			if (mapChipData[i][j] == (int)MapInfo::NONE)
			{
				chipData[i][j] = ChipData::Create(i, j, MapInfo::NONE);

			}
			
			if (mapChipData[i][j] == (int)MapInfo::ONES)
			{
				chipData[i][j] = ChipData::Create(i, j, MapInfo::ONES);
			}
		}
	}
}

void MapChip2D::Draw()
{
	for (int i = 0; i < sizeX_.size(); i++)
	{
		for (int j = 0; j < sizeY_.size(); j++)
		{
			
			chipData[i][j]->Draw();
		}
	}
}

void MapChip2D::Delete()
{
	for (int i = 0; i < sizeX_.size(); i++)
	{
		for (int j = 0; j < sizeY_.size(); j++)
		{

			chipData[i][j]->Delete();
		}
	}
}
