#include "GameScene.h"
#include "ExternalFileLoader.h"

void GameScene::Initialize()
{
	const Vector3 LB = { -1.0f, -0.7f, 0.0f };
	const Vector3 LT = { -1.0f, +1.0f, 0.0f };
	const Vector3 RB = { +0.85f, -0.7f, 0.0f };
	const Vector3 RT = { +0.85f, +1.0f, 0.0f };
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

	postEffectNo_ = PostEffect::NONE;

	enemys_ = new Enemys();
	enemys_ = Enemys::Create();

	//blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);
	//player_ = Player::Create();
	RoadPlayer();
	bgSprite_ = Sprite::Create(UINT(ImageManager::ImageName::bgTexNumber), { 0,0 });
	GameSprite1 = Sprite::Create(UINT(ImageManager::ImageName::GameUI_01), { 0,0 });
	GameSprite2 = Sprite::Create(UINT(ImageManager::ImageName::GameUI_02), { 0,0 });
	GameSprite3 = Sprite::Create(UINT(ImageManager::ImageName::GameUI_03), { 0,0 });
	manual = Sprite::Create(UINT(ImageManager::ImageName::Manual), { 300,0 });
	int32_t towerHP = 10;
	tower_ = new Tower;
	tower_->Initialize(towerHP);
	scrollCamera_ = ScrollCamera::Create();
	Sprite::SetCamera(scrollCamera_);
	bloodGaugeSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::bloodGaugeNumber), { 100,0 });
	bloodGaugeSprite_->SetLeftSizeCorrection(true);
	bloodGaugeSprite_->SetUi(true);
	poseButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Pause, { 64,24 }, { 100,100 }, 0);
	poseBackButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Back, { 100,300 }, { 100,100 }, 0);
	titleButton_ = Button::CreateUniqueButton(ImageManager::ImageName::TitleBack, { 100,400 }, { 100,100 }, 0);

	camera2D = new Camera2D();
	camera2D->InitializeCamera(WinApp::window_width, WinApp::window_height);
	Sprite::SetCamera2D(camera2D);
}

void GameScene::Update()
{
	//blood_->Update();
	HitBloodAndEnemys();
	HitTowerAndEnemys();

	poseButton_->Update();
	tower_->Update();
	if (poseButton_->GetIsClick()) {
		pose_ = true;
	}
	if (pose_) {
		poseBackButton_->Update();
		titleButton_->Update();
		if (poseBackButton_->GetIsClick()) {
			pose_ = false;
		}
	}
	else {
		DirectX::XMVECTOR LB = { -1.0f, -0.7f, 0.0f };
		DirectX::XMVECTOR LT = { -1.0f, +1.0f, 0.0f };
		DirectX::XMVECTOR RB = { +0.85f, -0.7f, 0.0f };
		DirectX::XMVECTOR RT = { +0.85f, +1.0f, 0.0f };

		DirectX::XMVECTOR LB2 = DirectX::XMVector3TransformCoord(LB, camera2D->GetMatViewPort());
		DirectX::XMVECTOR LT2 = DirectX::XMVector3TransformCoord(LT, camera2D->GetMatViewPort());
		DirectX::XMVECTOR RB2 = DirectX::XMVector3TransformCoord(RB, camera2D->GetMatViewPort());
		DirectX::XMVECTOR RT2 = DirectX::XMVector3TransformCoord(RT, camera2D->GetMatViewPort());

		float otoko = RB2.m128_f32[0] / (float)WinApp::window_width;
		float otoko2 = RB2.m128_f32[1] / (float)WinApp::window_height;
		player_->SetPosition({ MouseInput::GetIns()->GetMousePoint().x * otoko,MouseInput::GetIns()->GetMousePoint().y * otoko2 });
		//player_->SetPosition({ MouseInput::GetIns()->GetMousePoint().x + MouseInput::GetIns()->GetMousePoint().x * (1.0f - otoko + 0.005f),MouseInput::GetIns()->GetMousePoint().y + MouseInput::GetIns()->GetMousePoint().y * (1.0f - otoko2 + 0.005f) });
		player_->Update(scrollCamera_);
		//scrollCamera_->Update(player_->GetSprite()->GetPosition());

		int b = player_->GetBloodGauge();
		bloodGaugeSprite_->SetSize({ (float)16 * b ,16 });

		enemys_->Update(tower_->GetHP(), player_->GetPlayerHp());
	}
	//enemy_->Update();

	//�V�[���؂�ւ�
	SceneChange();
}

void GameScene::HitBloodAndEnemys()
{

	for (auto& vampire : enemys_->GetVampires())
	{
		for (auto& blood : player_->GetBloods())
		{
			bool isHit = Collision::HitCircle(vampire->Getpos(), 32, blood->GetPos(), 16);

			if (isHit == true)
			{
				vampire->SetBloadHitFlag(isHit);
				vampire->SetBloodType(blood->GetTemperature());
			}
		}
	}

	for (auto& basilisk : enemys_->GetBasiliskes())
	{
		for (auto& blood : player_->GetBloods())
		{
			bool isHit = Collision::HitCircle(basilisk->Getpos(), 32, blood->GetPos(), 16);

			if (isHit == true)
			{
				basilisk->SetBloadHitFlag(isHit);
				basilisk->SetBloodType(blood->GetTemperature());
			}
		}
	}

	for (auto& rabbit : enemys_->GetRabbits())
	{
		for (auto& blood : player_->GetBloods())
		{
			bool isHit = Collision::HitCircle(rabbit->Getpos(), 32, blood->GetPos(), 16);

			if (isHit == true)
			{
				rabbit->SetBloadHitFlag(isHit);
				rabbit->SetBloodType(blood->GetTemperature());
			}
		}
	}

	//enemys_->SetEnemys(enemy_1);

}

void GameScene::HitTowerAndEnemys()
{
	for (auto& vampire : enemys_->GetVampires())
	{
		bool isHit = Collision::HitCircle(vampire->Getpos(), 32, tower_->GetPos(), 16);
		if (isHit)
		{
			tower_->OnCollision();
			vampire->OnCollision();
		}
	}

	for (auto& basilisk : enemys_->GetBasiliskes())
	{
		bool isHit = Collision::HitCircle(basilisk->Getpos(), 32, tower_->GetPos(), 16);
		if (isHit)
		{
			tower_->OnCollision();
			basilisk->OnCollision();

		}
	}

	for (auto& rabbit : enemys_->GetRabbits())
	{
		bool isHit = Collision::HitCircle(rabbit->Getpos(), 32, tower_->GetPos(), 16);
		if (isHit)
		{
			tower_->OnCollision();
			rabbit->OnCollision();

		}
	}
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
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	bgSprite_->Draw();
	player_->Draw(scrollCamera_);
	tower_->Draw();
	//enemy_->Draw();
	enemys_->Draw();
	Sprite::PostDraw();
	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	D2D1_RECT_F textDrawRange2 = { 0, 100, 500, 500 };
	//text_->Draw("meiryo", "white", L"�Q�[���V�[��\n���N���b�N�Ń^�C�g���V�[��\n�E�N���b�N�Ń��U���g�V�[��", textDrawRange);
	DirectX::XMVECTOR LB = { -1.0f, -0.7f, 0.0f };
	DirectX::XMVECTOR LT = { -1.0f, +1.0f, 0.0f };
	DirectX::XMVECTOR RB = { +0.85f, -0.7f, 0.0f };
	DirectX::XMVECTOR RT = { +0.85f, +1.0f, 0.0f };
	DirectX::XMVECTOR LB2 = DirectX::XMVector3TransformCoord(LB, camera2D->GetMatViewPort());
	DirectX::XMVECTOR LT2 = DirectX::XMVector3TransformCoord(LT, camera2D->GetMatViewPort());
	DirectX::XMVECTOR RB2 = DirectX::XMVector3TransformCoord(RB, camera2D->GetMatViewPort());
	DirectX::XMVECTOR RT2 = DirectX::XMVector3TransformCoord(RT, camera2D->GetMatViewPort());

	float otoko = RB2.m128_f32[0] / WinApp::window_width;
	float otoko2 = RB2.m128_f32[1] / WinApp::window_height;

	std::wstring unti = std::to_wstring(MouseInput::GetIns()->GetMousePoint().x * otoko);
	std::wstring unti2 = std::to_wstring(MouseInput::GetIns()->GetMousePoint().y * otoko2);
	std::wstring tintin = std::to_wstring(player_->GetSprite()->GetPosition().x);
	std::wstring tintin2 = std::to_wstring(player_->GetSprite()->GetPosition().y);

	int ketu = MouseInput::GetIns()->GetMousePoint().x;

	text_->Draw("meiryo", "white", unti + L"\n" + unti2, textDrawRange);
	text_->Draw("meiryo", "white", tintin + L"\n" + tintin2, textDrawRange2);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	//�|�X�g�G�t�F�N�g�`��
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);

	//�|�X�g�G�t�F�N�g�������Ȃ��X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	bloodGaugeSprite_->Draw();
	poseButton_->Draw();
	//GameSprite1->Draw();
	//GameSprite2->Draw();
	//GameSprite3->Draw();
	if (pose_) {
		poseBackButton_->Draw();
		titleButton_->Draw();
		manual->Draw();
	}
	Sprite::PostDraw();
	DirectXSetting::GetIns()->PostDraw();
}


void GameScene::Finalize()
{
	safe_delete(text_);
	//enemys_->Delete();
	safe_delete(enemys_);
	safe_delete(manual);

	safe_delete(player_);
	safe_delete(bgSprite_);
	safe_delete(GameSprite1);
	safe_delete(GameSprite2);
	safe_delete(GameSprite3);
	safe_delete(tower_);
	safe_delete(scrollCamera_);
	safe_delete(camera2D);
	Sprite::SetCamera2D(nullptr);
}

void GameScene::HitEnemys()
{

}

void GameScene::SceneChange()
{
	if (pose_ && titleButton_->GetIsClick()) {
		SceneManager::SceneChange(SceneManager::SceneName::Title);
	}
	else if (enemys_->GetGameFlag() == 1)
	{
		SceneManager::SceneChange(SceneManager::SceneName::Result);
	}
	else if (tower_->GetHP() <= 0)
	{
		//SceneManager::SceneChange(SceneManager::SceneName::Over);

	}
}

void GameScene::RoadPlayer()
{
	std::string line;
	Vector2 pos{};
	int rote, maxBlood = 0, hp = 0;
	std::stringstream stream = ExternalFileLoader::GetIns()->ExternalFileOpen("player.txt");

	while (getline(stream, line)) {
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ' ');

		if (word.find("#") == 0) {
			continue;
		}
		if (word.find("pos") == 0) {
			line_stream >> pos.x;
			line_stream >> pos.y;
		}
		if (word.find("rote") == 0) {
			line_stream >> rote;
		}
		if (word.find("maxBlood") == 0) {
			line_stream >> maxBlood;
		}
		if (word.find("hp") == 0) {
			line_stream >> hp;
		}
	}
	player_ = Player::Create(pos, rote, hp, maxBlood);
}

