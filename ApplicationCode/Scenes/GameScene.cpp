#include "GameScene.h"
#include "ExternalFileLoader.h"
#include "KeyInput.h"

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

	enemys_ = EnemyManager::Create();

	//blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);
	//player_ = Player::Create();
	RoadPlayer();
	bgSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::bgTexNumber), { 0,0 });
	GameSprite1_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_01), { 0,0 });
	GameSprite2_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_02), { 0,0 });
	GameSprite3_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_03), { 0,0 });
	GameSprite1_->SetUi(true);
	GameSprite2_->SetUi(true);
	playerHp = Sprite::Create(UINT(ImageManager::ImageName::playerHp), { 0,0 });
	playerHp->SetUi(true);

	reticleSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::reticle), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	reticleSprite_->SetUi(true);

	manual_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::Manual), { 300,0 });
	manual_->SetUi(true);
	int32_t towerHP = 10;
	tower_ = new Tower;
	tower_->Initialize(towerHP);
	scrollCamera_ = ScrollCamera::Create();
	Sprite::SetCamera(scrollCamera_);
	// 血の量
	bloodGaugeSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::bloodGaugeNumber), { 99,656 });
	bloodGaugeSprite_->SetLeftSizeCorrection(true);
	bloodGaugeSprite_->SetUi(true);
	// 体温
	ultGaugeSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 });
	ultGaugeSprite_->SetLeftSizeCorrection(true);
	ultGaugeSprite_->SetUi(true);
	// オーバーヒート状態
	overheatSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::overheatNumber), { 1196,375 });
	overheatSprite_->SetLeftSizeCorrection(true);
	overheatSprite_->SetUi(true);

	poseButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Pause, { 64,24 }, { 100,100 }, 0);
	poseBackButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Back, { 100,300 }, { 100,100 }, 0);
	titleButton_ = Button::CreateUniqueButton(ImageManager::ImageName::TitleBack, { 100,400 }, { 100,100 }, 0);

	camera2D = new Camera2D();
	camera2D->InitializeCamera(WinApp::window_width, WinApp::window_height);
	Sprite::SetCamera2D(camera2D);

	timer_ = new Timer();
	timer_->Initialize(60 * 20);

	mapChip2D = MapChip2D::Create();
	mapChip2D->Ins();

	marker_ = ArrowMarker::Create({ 640, 360 });
}

void GameScene::Update()
{
	//blood_->Update();
	HitBloodAndEnemys();
	HitTowerAndEnemys();
	timer_->Update();

	poseButton_->Update();
	tower_->Update();

	if (KeyInput::GetIns()->TriggerKey(DIK_M)) {
		debugMuteki = !debugMuteki;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_O)) {
		timer_->SetIsWatchOpen(true);
	}
	else if (KeyInput::GetIns()->TriggerKey(DIK_C)) {
		timer_->SetIsWatchOpen(false);
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_S)) {
		timer_->SetIsTimerStart(true);
	}

	if (poseButton_->GetIsClick()) {
		pose_ = true;
		ShowCursor(true);

	}
	if (pose_) {
		poseBackButton_->Update();
		titleButton_->Update();
		if (poseBackButton_->GetIsClick()) {
			ShowCursor(false);
			pose_ = false;
		}
	}
	else {
		player_->Update(scrollCamera_);
		//scrollCamera_->Update(player_->GetSprite()->GetPosition());

		int bloodGauge = player_->GetBloodGauge();
		//						横幅(1090)を10で割った数,縦幅
		bloodGaugeSprite_->SetSize({ (float)1090 / player_->GetMaxBloodGauge() * bloodGauge,27 });							// 血量バーの大きさを変える
		float u = player_->GetUltGauge();
		const float ultSpriteMaxSizeX = 36.f; const float ultSpriteMaxSizeY = 336.f;
		ultGaugeSprite_->SetSize({ ultSpriteMaxSizeX,(ultSpriteMaxSizeY / player_->GetUltMaxGauge()) * -u });	// 体温バーの大きさを変える

		overheatSprite_->SetSize({ ultSpriteMaxSizeX,(ultSpriteMaxSizeY / player_->GetUltMaxGauge()) * -u });	// 体温バーの大きさを変える

		enemys_->Update(tower_->GetHP(), player_->GetPlayerHp(), scrollCamera_->GetPosition());
	}

	marker_->Update(scrollCamera_->GetPosition());

	//enemy_->Update();
	scrollCamera_->Update(player_->GetPosition());
	reticleSprite_->SetPosition({ (float)MouseInput::GetIns()->GetMousePoint().x,(float)MouseInput::GetIns()->GetMousePoint().y });
	//シーン切り替え
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
	bgSprite_->Draw();
	player_->Draw(scrollCamera_);
	tower_->Draw();
	//enemy_->Draw();
	enemys_->Draw();
	mapChip2D->Draw();
	marker_->Draw();
	Sprite::PostDraw();
	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//テキスト描画範囲
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };

	/*std::wstring wstr1 = std::to_wstring(player_->GetPosition().x);
	std::wstring wstr2 = std::to_wstring(player_->GetPosition().y);*/

	std::wstring wstr1 = std::to_wstring(MouseInput::GetIns()->GetMousePoint().x);
	std::wstring wstr2 = std::to_wstring(MouseInput::GetIns()->GetMousePoint().y);

	DirectX::XMVECTOR vec = { scrollCamera_->GetPosition().x,scrollCamera_->GetPosition().y };
	vec = DirectX::XMVector3TransformCoord(vec, Camera::GetMatViewPort());

	std::wstring wstr3 = std::to_wstring(scrollCamera_->GetPosition().x);
	std::wstring wstr4 = std::to_wstring(scrollCamera_->GetPosition().y);
	text_->Draw("meiryo", "white", wstr1 + L"\n" + wstr2 + L"\n" + wstr3 + L"\n" + wstr4, textDrawRange);


	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	//ポストエフェクト描画
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);

	//ポストエフェクトをかけないスプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	poseButton_->Draw();
	GameSprite1_->Draw();
	ultGaugeSprite_->Draw();
	if (player_->GetUltState()) {
		overheatSprite_->Draw();
	}
	GameSprite2_->Draw();
	//GameSprite3_->Draw();
	bloodGaugeSprite_->Draw();
	playerHp->Draw();
	reticleSprite_->Draw();

	if (pose_) {
		poseBackButton_->Draw();
		titleButton_->Draw();
		manual_->Draw();
	}
	timer_->Draw();
	Sprite::PostDraw();
	DirectXSetting::GetIns()->PostDraw();
}


void GameScene::Finalize()
{
	safe_delete(text_);
	//enemys_->Delete();
	safe_delete(enemys_);
	safe_delete(timer_);
	safe_delete(player_);
	safe_delete(playerHp);
	safe_delete(tower_);
	safe_delete(scrollCamera_);
	safe_delete(camera2D);
	mapChip2D->Delete();
	safe_delete(mapChip2D);
	safe_delete(marker_);
	Sprite::SetCamera2D(nullptr);
}

void GameScene::HitEnemys()
{

}

Vector2 GameScene::GetWorldMousePos()
{
	Vector2 mousePos{};
	mousePos.x = MouseInput::GetIns()->GetMousePoint().x;
	mousePos.y = MouseInput::GetIns()->GetMousePoint().y;
	mousePos += scrollCamera_->GetPosition();
	return mousePos;
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
	else if (tower_->GetHP() <= 0 && !debugMuteki)
	{
		SceneManager::SceneChange(SceneManager::SceneName::Over);

	}
}

void GameScene::RoadPlayer()
{
	std::string line;
	Vector2 pos{};
	float rote = 0.0f;
	int maxBlood = 0, hp = 0;
	std::stringstream stream = ExternalFileLoader::GetIns()->ExternalFileOpen("player.txt");

	while (getline(stream, line)) {
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ' ');

		if (word.find("#") == 0) {
			continue;
		}
		if (word.find("pos_") == 0) {
			line_stream >> pos.x;
			line_stream >> pos.y;
		}
		if (word.find("rote_") == 0) {
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

