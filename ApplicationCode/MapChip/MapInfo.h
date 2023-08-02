#pragma once
#include"ImageManager.h"
using ImageName = ImageManager::ImageName;
enum class MapInfo
{
	//マップの種類だけ増えていく名前は仮
	NONE,
	ONE,
	WALL,
	GORL
};


enum class MapCostInfo
{
	OFF,
	ON,
};