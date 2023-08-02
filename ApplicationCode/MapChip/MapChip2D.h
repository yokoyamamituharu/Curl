#pragma once
#include"ChipData.h"
#include"Vector2.h"
#include"..\AStar.h"
class MapChip2D
{


private:
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	static MapChip2D* Create();
	void MapChipDataCreate();
	void ChipDataCreate();
	void CostDataCreate();
	void Ins();
	void Update(Vector2 MousePos);
	void Draw();

	void Delete();
	ChipData* GetChipData(int sizeY, int sizeX) {return chipData[sizeY][sizeX];}
	XMFLOAT2 GetChipPos(int sizeY, int sizeX) { return chipData[sizeY][sizeX]->GetPos(); }
	bool GetFlag(int sizeY, int sizeX) { return chipData[sizeY][sizeX]->GetDrawFlag(); }

	int GetCost(int sizeY, int sizeX) { return chipData[sizeY][sizeX]->GetCost(); }

	int GetMapChipData(int sizeY, int sizeX) { return mapChipData[sizeY][sizeX]; }

	XMFLOAT2 GetTowerPos()
	{
	
		return towerPos_;
	}
	Cell GetTowerCell()
	{
		return towerCell_;
	}
	//int* GetCost() { return *mapChipCostData; }
private:
	std::array<int, 52> sizeX_;
	std::array<int, 43> sizeY_;
	ChipData* chipData[43][52]{};

	XMFLOAT2 towerPos_;
	Cell towerCell_;
	int mapChipData[43][52]{};

	int mapChipCostData[43][52]{};
};

