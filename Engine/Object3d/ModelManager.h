#pragma once
#include "Model.h"
#include "FBXLoader.h"
#include <map>
#include <vector>

class ModelManager
{
private:
	ModelManager() = default;
	~ModelManager();
	ModelManager(const ModelManager & obj) = delete;
	ModelManager& operator=(const ModelManager & obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ModelManager* GetIns();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���f���ǉ�
	/// </summary>
	/// <param name="modelName">�ǂݍ��݂������f����</param>
	/// <param name="modelKey">�A�N�Z�X���郂�f���̃L�[</param>
	/// <param name="isSmoothing">�X���[�W���O�������邩�ǂ���</param>
	void LoadModel(const std::string modelName, const std::string modelKey, bool isSmoothing = false);

	/// <summary>
	/// FBX���f���ǉ�
	/// </summary>
	/// <param name="modelName">���f����</param>
	void LoadFBXModel(const std::string modelName, const std::string modelKey);

	/// <summary>
	/// ���f���擾
	/// </summary>
	/// <param name="modelKey">���f���L�[</param>
	/// <returns>���f��</returns>
	Model* GetModel(const std::string modelKey) { return models_[modelKey]; }

	/// <summary>
	/// FBX���f���擾
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns>FBX���f��</returns>
	FBXModel* GetFBXModel(const std::string modelKey) { return fbxModels_[modelKey]; }

private: //�����o�ϐ�
	//std::vector<Model*> models;
	std::map<std::string, Model*> models_;
	std::map<std::string, FBXModel*> fbxModels_;
};

