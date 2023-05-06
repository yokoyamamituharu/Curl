#include "SceneManager.h"

BaseScene* SceneManager::nowScene = nullptr;
int32_t SceneManager::stageNo = 1;
int32_t SceneManager::score = 0;

void SceneManager::Initialize() {
	//�}�E�X�J�[�\�����\���ɂ���
	//ShowCursor(false);
	//DirectWrite������
	textDraw = std::make_unique<TextDraw>();
	textDraw->Initialize();
	//�V�[���؂�ւ�
	SceneChange(SceneName::Title);
}

void SceneManager::Update() {
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}

void SceneManager::Finalize() {
	//���݂̃V�[���̏I������
	nowScene->Finalize();
	//�x�[�X�V�[�����
	safe_delete(nowScene);
	//�J�[�\������
	//ShowCursor(true);
}

void SceneManager::AddScore(const int32_t score) {
	SceneManager::score += score;
}

void SceneManager::SetScore(const int32_t score)
{
	SceneManager::score = score;
}

void SceneManager::SceneChange(SceneName scene) {
	if (nowScene != nullptr) {
		nowScene->Finalize();
		safe_delete(nowScene);
	}

	switch (scene) {
	case SceneName::Title:
		nowScene = new TitleScene();
		nowScene->Initialize();
		break;
	case SceneName::Game:
		nowScene = new GameScene();
		nowScene->Initialize();
		break;
	case SceneName::Result:
		nowScene = new ResultScene();
		nowScene->Initialize();
		break;
	default:
		break;
	}
}