#include "SelectScene.h"
#include "SceneManager.h"
#include "ImageManager.h"

void SelectScene::Initialize()
{
	const Vector3 LB = { -1.0f, -1.0f, 0.0f };
	const Vector3 LT = { -1.0f, +1.0f, 0.0f };
	const Vector3 RB = { +1.0f, -1.0f, 0.0f };
	const Vector3 RT = { +1.0f, +1.0f, 0.0f };
	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize(LT, LB, RT, RB);

	tutorial_ = Button::CreateUniqueButton(ImageManager::ImageName::ManualButton, { 640, 200 }, { 128, 64 }, 0.0f);
	stage1_ = Button::CreateUniqueButton(ImageManager::ImageName::StartButton, {640, 400}, {128, 64}, 0.0f);
}

void SelectScene::Update()
{
	tutorial_->Update();
	stage1_->Update();

	SceneChange();
}

void SelectScene::Draw()
{
	//背景色
	const DirectX::XMFLOAT4 backColor = { 0.5f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	tutorial_->Draw();
	stage1_->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//テキスト描画範囲
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	//text_->Draw("meiryo", "white", L"リザルトシーン\n左クリックでゲームシーン\n右クリックでタイトルシーン", textDrawRange);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, PostEffect::NONE, true);
	DirectXSetting::GetIns()->PostDraw();
}

void SelectScene::Finalize()
{
}

void SelectScene::SceneChange()
{
	if (tutorial_->GetIsClick()) {
		SceneManager::SetStageNo(0);
		SceneManager::SceneChange(SceneManager::SceneName::Game);
	}
	else if (stage1_->GetIsClick()) {
		SceneManager::SetStageNo(1);
		SceneManager::SceneChange(SceneManager::SceneName::Game);
	}
}
