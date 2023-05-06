#include "ResultScene.h"

void ResultScene::Initialize()
{
	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize();

	light_ = LightGroup::UniquePtrCreate();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	//light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_.get());

	ground_ = Object3d::UniquePtrCreate(ModelManager::GetIns()->GetModel("ground"));
	ground_->SetScale({ 10.0f, 1.0f, 10.0f });
	ground_->SetPosition({ 0.0f, -10.0f, 0.0f });

	postEffectNo_ = PostEffect::NONE;
}

void ResultScene::Update()
{
	ground_->Update();
	//シーン切り替え
	SceneChange();
}

void ResultScene::Draw()
{
	//背景色
	const DirectX::XMFLOAT4 backColor = { 0.5f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground_->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//テキスト描画範囲
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	text_->Draw("meiryo", "white", L"リザルトシーン\n左クリックでゲームシーン\n右クリックでタイトルシーン", textDrawRange);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();
}

void ResultScene::Finalize()
{
	safe_delete(text_);
}

void ResultScene::SceneChange()
{
	if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::SceneName::Game);
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::RIGHT_CLICK)) {
		SceneManager::SceneChange(SceneManager::SceneName::Title);
	}
}
