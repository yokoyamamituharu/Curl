#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include <list>
#include "Vector3.h"
#include "Object3d.h"
#include "ModelManager.h"

class JsonLoader
{
public:
	//�X�e�[�W�I�u�W�F�N�g�f�[�^
	struct StageData {
		struct ObjectData {
			std::string fileName_;
			Vector3 transform_;
			Vector3 rotation_;
			Vector3 scaling_;
			bool isWave_;
		};
		std::vector<ObjectData> stageObjects_;
	};

	enum class EnemyType {
		STR,
		AIM
	};

	struct EnemyData {
		struct EnemyStatus {
			std::string fileName_;
			Vector3 transform_;
			Vector3 rotation_;
			Vector3 scaling_;
			JsonLoader::EnemyType enemyType_;
			int32_t waitTime_;
			int32_t lifeTime_;
			int32_t shotCoolTime_;
			int32_t hp_;
		};
		std::vector<EnemyStatus> enemyObjects_;
	};

public:
	JsonLoader() = default;
	~JsonLoader() = default;

public: //�����o�֐�
	/// <summary>
	/// �X�e�[�W�f�[�^json�t�@�C���ǂݍ��݋y�ѐ���
	/// </summary>
	/// <param name="fileName">json�t�@�C��</param>
	void StageDataLoadandSet(const std::string fileName);

	/// <summary>
	/// �G�l�~�[�f�[�^json�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName"></param>
	void EnemyDataLoad(const std::string fileName);

	/// <summary>
	/// �G�l�~�[�f�[�^�X�V����
	/// </summary>
	/// <param name="isPause">�|�[�Y�t���O</param>
	void EnemyDataUpdate(bool isPause);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�ÓI�����o�ϐ�
	static const std::string baseDirectory;
	static const std::string extension;

private: //�����o�ϐ�
	//�X�e�[�W�I�u�W�F�N�g
	std::list<std::unique_ptr<Object3d>> allObjects_;
	//�G�l�~�[json�f�[�^
	nlohmann::json enemyJsonData_;
	//�|�b�v�ҋ@�t���O
	bool isWait_;
	//�|�b�v�ҋ@�^�C�}�[
	int32_t waitTimer_;
};