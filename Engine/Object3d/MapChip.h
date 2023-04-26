#pragma once
#include "Model.h"
#include "Object3d.h"
#include "SafeDelete.h"

class MapChip
{
public: //�����o�֐�
	/// <summary>
	/// �}�b�v�`�b�v�̏�����
	/// </summary>
	void MapChipInitialize();

	/// <summary>
	/// �}�b�v�`�b�v�̃��[�h
	/// </summary>
	/// <param name="mapname">csv�t�@�C����</param>
	/// <param name="map_Width">����</param>
	/// <param name="map_Height">�c��</param>
	/// <returns>�}�b�v�`�b�v</returns>
	int32_t** MapLoad(const std::string& mapname, int32_t map_width, int32_t map_height);

	/// <summary>
	/// �}�b�v�`�b�v�̃Z�b�g
	/// </summary>
	/// <param name="map">�ǂݍ��񂾃}�b�v�`�b�v</param>
	/// <param name="map_Width">����</param>
	/// <param name="map_Height">�c��</param>
	/// <param name="height">�}�b�v�̍���(0�Ȃ�n��)</param>
	/// <returns>�}�b�v�`�b�v���I�u�W�F�N�g�ɃZ�b�g</returns>
	std::vector<Object3d*> MapSet(int32_t** map, int32_t map_Width, int32_t map_Height, int32_t height);

	/// <summary>
	/// �}�b�v�`�b�v�̉��
	/// </summary>
	void MapChipFinalize();

private: //�����o�ϐ�
	//�u���b�N����̑傫��
	//const float LAND_SCALE = 30.0f;
	int32_t** map;

	Model* blockModel = nullptr;
};

