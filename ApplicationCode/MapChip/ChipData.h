#pragma once
#include "Sprite.h"
#include <map>
#include<array>
#include "ImageManager.h"
#include"MapInfo.h"
class ChipData
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;

private:

public:
	
	static ChipData* Create(int i, int j, const ImageName name);
	
	void Ins(int i, int j, const ImageName name);
	void Mapping(int i, int j);
	void Draw();
	void Delete();

	void CostOn() { this->cost_ = 1; }
	void SetCost(int cost) { this->cost_ = cost; }
	int GetCost() { return cost_; }
	XMFLOAT2 GetPos() { return pos_; }
	int GetChipNumber() { return chipNumber; }
private:

	Sprite* sprite_{};
	XMFLOAT2 pos_{};

	int chipNumber;
	int cost_ = 0;
	std::array<int, 64> size_;
};

