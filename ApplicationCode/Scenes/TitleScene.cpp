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
	//�V�[���؂�ւ�
	SceneChange();
}

void TitleScene::Draw()
{
	//�w�i�F
	const DirectX::XMFLOAT4 backColor = { 0.5f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	
	if(manualFlag ==0)title_->Draw();
	if (manualFlag == 1)manual_->Draw();

	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	gameButton_->Draw();
	if (manualFlag == 0)manualButton_->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	//text_->Draw("meiryo", "white", L"�^�C�g���V�[��\n���N���b�N�Ń��U���g�V�[��\n�E�N���b�N�ŃQ�[���V�[��", textDrawRange);
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
