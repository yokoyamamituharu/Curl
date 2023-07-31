#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "DirectXSetting.h"
#include "Sound.h"
#include "KeyInput.h"
#include "SafeDelete.h"
#include "TextDraw.h"
#include "SelectScene.h"
#include "OverScene.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

public: //�V�[���Ǘ��ԍ�
	enum class SceneName {
		Title,
		Select,
		Game,
		Result,
		Over,
		None
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

public: //�ÓI�����o�֐�

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update();

	/// <summary>
	/// �`��
	/// </summary>
	static void Draw();

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	static void SceneChange(SceneName scene);

	/// <summary>
	/// �X�R�A�����Z
	/// </summary>
	/// <param name="score">�X�R�A</param>
	static void AddScore(const int32_t score);

	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="score"></param>
	static void SetScore(const int32_t score);

	/// <summary>
	/// �X�e�[�W�ԍ����Z�b�g
	/// </summary>
	static void SetStageNo(const int32_t stageNo);

	/// <summary>
	/// �X�e�[�W�ԍ��擾
	/// </summary>
	/// <returns>�X�e�[�W�ԍ�</returns>
	static int32_t GetStageNo() { return stageNo_; }

	/// <summary>
	/// �X�R�A�擾
	/// </summary>
	/// <returns>�X�R�A</returns>
	static int32_t GetScore() { return score; }

private: //�ÓI�����o�ϐ�
	static BaseScene* nowScene;
	static int32_t stageNo_;
	static int32_t score;

private: //�����o�ϐ�
	std::unique_ptr<TextDraw> textDraw;
};