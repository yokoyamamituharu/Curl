#include "MapChip2D.h"

MapChip2D* MapChip2D::Create()
{
	MapChip2D* instance = new MapChip2D();
	return instance;
}

void MapChip2D::MapChipData()
{
	//�X�e�[�W�\��
	//[][]������̒��g�͍ő吔�ɉ����ĕς���
	//�ő吔�̐ݒ��sizeX_��sizeY_�Őݒ�
	int temp[10][10] =
	{
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,}
	};
	//�X�e�[�W�f�[�^���
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
	//�X�e�[�W�쐬
	MapChipData();

	for (int i = 0; i < sizeX_.size(); i++)
	{
		for (int j = 0; j < sizeY_.size(); j++)
		{
			//�`�b�v���ꂼ��̔ԍ��ɂ���č쐬
			if (mapChipData[i][j] == NONE)
			{
				chipData[i][j] = ChipData::Create(i, j, NONE);
			}
			
			if (mapChipData[i][j] == ONES)
			{
				chipData[i][j] = ChipData::Create(i, j, ONES);
			}
		}
	}
}
