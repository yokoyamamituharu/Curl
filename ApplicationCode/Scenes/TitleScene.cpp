#include "TitleScene.h"
#include <random>

void TitleScene::Initialize()
{
	const Vector3 LB = { -1.0f, -1.0f, 0.0f };
	const Vector3 LT = { -1.0f, +1.0f, 0.0f };
	const Vector3 RB = { +1.0f, -1.0f, 0.0f };
	const Vector3 RT = { +1.0f, +1.0f, 0.0f };
	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize(LT, LB, RT, RB);

	light_ = LightGroup::UniquePtrCreate();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	//light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_.get());
	manualFlag = 0;
	title_ = Sprite::Create((UINT)ImageManager::ImageName::TitleLog, {});
	title_->SetSize({ 400*2,400*2 });
	manual_ = Sprite::Create((UINT)ImageManager::ImageName::Manual, {});
	postEffectNo_ = PostEffect::NONE;
	gameButton_ = Button::CreateUniqueButton(ImageManager::ImageName::StartButton, { 1000,400 }, { 100,100 }, 0);
	manualButton_ = Button::CreateUniqueButton(ImageManager::ImageName::ManualButton, { 1000,600 }, { 100,100 }, 0);
}

void TitleScene::Update()
{
	gameButton_->Update();
	if(manualFlag == 0)manualButton_->Update();
	//シーン切り替え
	SceneChange();
}

void TitleScene::Draw()
{
	//背景色
	const DirectX::XMFLOAT4 backColor = { 0.5f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	
	if(manualFlag ==0)title_->Draw();
	if (manualFlag == 1)manual_->Draw();

	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	gameButton_->Draw();
	if (manualFlag == 0)manualButton_->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//テキスト描画範囲
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	//text_->Draw("meiryo", "white", L"タイトルシーン\n左クリックでリザルトシーン\n右クリックでゲームシーン", textDrawRange);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();
}


void TitleScene::Finalize()
{
	safe_delete(text_);
	safe_delete(title_);
	safe_delete(manual_);
}

void TitleScene::SceneChange()
{
	if (gameButton_->GetIsClick()) {
		SceneManager::SceneChange(SceneManager::SceneName::Game);

	}
	else if (manualButton_->GetIsClick()) {

		manualFlag = 1;
	}
}
