#pragma once
#include"ImageManager.h"
using ImageName = ImageManager::ImageName;
enum class MapInfo
{
	//�}�b�v�̎�ނ��������Ă������O�͉�
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