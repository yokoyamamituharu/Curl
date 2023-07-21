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
	
	static ChipData* Create(int i, int j, const MapInfo name);
	
	void Ins(int i, int j, const MapInfo name);
	void Mapping(int i, int j);
	void Draw();
	void Delete();
	XMFLOAT2 GetPos() { return pos_; }
	int GetChipNumber() { return chipNumber; }
private:

	Sprite* sprite_{};
	XMFLOAT2 pos_{};

	int chipNumber;
	std::array<int, 64> size_;
};

