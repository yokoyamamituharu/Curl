#include "GameScene.h"

void GameScene::Initialize()
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

	blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);
	player_ = Player::Create();
	bgSprite_ = Sprite::Create(UINT(ImageManager::ImageName::bgTexNumber),{0,0});
	int32_t towerHP = 10;
	tower_ = new Tower;
	tower_->Initialize(towerHP);
	scrollCamera_ = ScrollCamera::Create();
	Sprite::SetCamera(scrollCamera_);
	player_->SetCamera(scrollCamera_);
}

void GameScene::Update()
{
	//blood_->Update();
	player_->Update();
	scrollCamera_->Update();
	ground_->Update();	
	//�V�[���؂�ւ�
	SceneChange();
}

void GameScene::Draw()
{
	//�w�i�F
	const DirectX::XMFLOAT4 backColor = { 0.5f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());	
	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground_->Draw();
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	bgSprite_->Draw();
	player_->Draw(scrollCamera_);
	tower_->Draw();
	//scrollCamera->Draw(player_->GetSprite());
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	text_->Draw("meiryo", "white", L"�Q�[���V�[��\n���N���b�N�Ń^�C�g���V�[��\n�E�N���b�N�Ń��U���g�V�[��", textDrawRange);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();
}

void GameScene::Finalize()
{
	safe_delete(text_);
	safe_delete(blood_);
	safe_delete(player_);
	safe_delete(bgSprite_);
	safe_delete(tower_);
	safe_delete(scrollCamera_);
}

void GameScene::SceneChange()
{
	if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::SceneName::Title);
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::RIGHT_CLICK)) {
		SceneManager::SceneChange(SceneManager::SceneName::Result);
	}
}
