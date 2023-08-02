#include "GameScene.h"
#include "ExternalFileLoader.h"
#include "KeyInput.h"

std::vector<Sprite*> GameScene::SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& UIpos) {
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, UIpos));
		sprites[i]->SetAnchorPoint({ 0.0f, 0.0f });
		sprites[i]->SetPosition(UIpos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 1280.0f * (float)i;
		sprites[i]->SetSize({ 1280.0f, 720.0f });
		sprites[i]->SetTextureRect(texBase, { 1280.0f, 720.0f });
	}
	return sprites;
}

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

	//blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);
	//player_ = Player::Create();
	RoadPlayer();
	bgSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::bgTexNumber), { 0,0 });
	bgSprite_->SetSize({ 3200.0f, 2700.0f });
	GameSprite1_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_01), { 0,0 });
	GameSprite2_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_02), { 0,0 });
	GameSprite3_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::GameUI_03), { 0,0 });
	GameSprite1_->SetUi(true);
	GameSprite2_->SetUi(true);

	towerUISprites_ = SpritesCreate(ImageManager::ImageName::TowerUI, towerUIAnimationMax, { 0,0 });
	for (int32_t i = 0; i < towerUIAnimationMax; i++) {
		towerUISprites_[i]->SetUi(true);
	}
	towerUIAnimationCount_ = 0;

	playerHp = Sprite::Create(UINT(ImageManager::ImageName::playerHp), { 0,0 });
	playerHp->SetUi(true);

	reticleSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::reticle), { 0,0 }, { 1,1,1,1 }, { 0.5,0.5 });
	reticleSprite_->SetUi(true);

	manual_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::Manual), { 300,0 });
	manual_->SetUi(true);
	int32_t towerHP = 2;
	tower_ = new Tower;
	tower_->Initialize(towerHP);
	scrollCamera_ = ScrollCamera::Create();
	Sprite::SetCamera(scrollCamera_);
	// 血の量
	bloodGaugeSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::bloodGaugeNumber), { 99,656 }, { 1.0f,0.0f,0.0f,0.0f });
	bloodGaugeSprite_->SetLeftSizeCorrection(true);
	bloodGaugeSprite_->SetUi(true);
	// 体温
	ultGaugeSprite_[0] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 0.0f, 0.0f, 1.0f, 1.0f });
	ultGaugeSprite_[0]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[0]->SetUi(true);
	ultGaugeSprite_[1] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 0.0f, 0.0f, 1.0f,1.0f });
	ultGaugeSprite_[1]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[1]->SetUi(true);
	ultGaugeSprite_[2] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 1.0f, 0.5f, 1.0f,1.0f });
	ultGaugeSprite_[2]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[2]->SetUi(true);
	ultGaugeSprite_[3] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 1.0f, 0.5f, 0.0f,1.0f });
	ultGaugeSprite_[3]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[3]->SetUi(true);
	ultGaugeSprite_[4] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 1.0f, 0.5f, 0.5f,1.0f });
	ultGaugeSprite_[4]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[4]->SetUi(true);
	ultGaugeSprite_[5] = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::ultGaugeNumber), { 1196,375 }, { 0.5f, 0.5f, 0.5f,1.0f });
	ultGaugeSprite_[5]->SetLeftSizeCorrection(true);
	ultGaugeSprite_[5]->SetUi(true);

	color[0] = { 1.0f, 0.0f, 0.0f };
	color[1] = { 1.0f,1.0f,0.0f };
	color[2] = { 0.5f, 0.5f,1.0f };
	color[3] = { 1.0f, 0.0f, 1.0f };
	color[4] = { 0.5f, 1.0f,0.5f };
	color[5] = { 0.5f, 0.5f,0.5f };

	ultGaugeSprite_[0]->SetColor(color[0]);
	ultGaugeSprite_[1]->SetColor(color[1]);
	ultGaugeSprite_[2]->SetColor(color[2]);
	ultGaugeSprite_[3]->SetColor(color[3]);
	ultGaugeSprite_[4]->SetColor(color[4]);
	ultGaugeSprite_[5]->SetColor(color[5]);

	// オーバーヒート状態
	//overheatSprite_ = Sprite::UniquePtrCreate(UINT(ImageManager::ImageName::overheatNumber), { 1196,375 });
	//overheatSprite_->SetLeftSizeCorrection(true);
	//overheatSprite_->SetUi(true);

	poseButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Pause, { 64,24 }, { 100,100 }, 0);
	poseBackButton_ = Button::CreateUniqueButton(ImageManager::ImageName::Back, { 100,300 }, { 100,100 }, 0);
	titleButton_ = Button::CreateUniqueButton(ImageManager::ImageName::TitleBack, { 100,400 }, { 100,100 }, 0);
	particle_ = ParticleManager2d::UniquePtrCreate();
	for (int32_t i = 0; i < 4; i++) {
		towerBreak_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::towerBreak, { 640, -500 });
		towerBreak_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		towerBreak_[i]->SetTextureRect({ 64.0f * (float)i, 0.0f }, { 64.0f, 64.0f });
		towerBreak_[i]->SetSize({ 256.0f, 256.0f });
		towerBreak_[i]->SetUi(true);
	}

	camera2D = new Camera2D();
	camera2D->InitializeCamera(WinApp::window_width, WinApp::window_height);
	Sprite::SetCamera2D(camera2D);

	timer_ = new Timer();
	timer_->Initialize(60 * 1);

	enemys_ = EnemyManager::Create();
	messageWindow_ = MessageWindow::UniquePtrCreate();
	messageWindow_->Initialize();

	if (SceneManager::GetStageNo() == 0) {
		enemys_->EnemySpawnDataLoad("Stage1_EnemySpawnData.csv");
		messageWindow_->LoadTextMessageData("TutorialMessage.csv");
		isTutorial_ = true;
	}
	else if (SceneManager::GetStageNo() == 1) {
		enemys_->EnemySpawnDataLoad("Stage1_EnemySpawnData.csv");
	}

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
	if (messageWindow_->GetIsLoadEnd()) {
		isTutorial_ = false;
		if (SceneManager::GetStageNo() == 0) {

		}
	}

	static int32_t timer = 0;
	if (timer++ > 5) {
		if (player_->GetUltLevel() == 0) {
			//particle_->Add(50, player_->GetPosition(), { 0, -1 }, { 0, 0 }, { 15.0f, 15.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[0], { 1.0f, 1.0f, 1.0f });
			}
		}
		else if (player_->GetUltLevel() == 1) {
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[1], { 1.0f, 1.0f, 1.0f });
			}
		}
		else if (player_->GetUltLevel() == 2) {
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[2], { 1.0f, 1.0f, 1.0f });
			}
		}
		else if (player_->GetUltLevel() == 3) {
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[3], { 1.0f, 1.0f, 1.0f });
			}
		}
		else if (player_->GetUltLevel() == 4) {
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[4], { 1.0f, 1.0f, 1.0f });
			}
		}
		else if (player_->GetUltLevel() == 5) {
			int iNum = (int)RandCreate::sGetRandFloat(1, 2);
			float fNum = (float)RandCreate::sGetRandFloat(-5, 5);
			for (int i = 0; i < iNum; i++) {
				Vector2 vec2 = { (float)RandCreate::sGetRandFloat(-10, 10), (float)RandCreate::sGetRandFloat(-10, 10) };
				particle_->Add(50, player_->GetPosition() + vec2, { 0, -1 }, { 0, 0 }, { 15.0f + fNum, 15.0f + fNum }, { 0.0f, 0.0f }, color[5], { 1.0f, 1.0f, 1.0f });
			}
		}
		timer = 0;
	}

	particle_->Update();
	poseButton_->Update();
	tower_->Update();

	if (KeyInput::GetIns()->TriggerKey(DIK_M)) {
		//debugMuteki = !debugMuteki;
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

	if (poseBreak) {
		if (!MouseInput::GetIns()->PushClick(MouseInput::MouseState::LEFT_CLICK)) {
			poseBreak = false;
		}
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
			poseBreak = true;
		}
	}
	else {
		//マップチップの位置に血を発射する
		if (poseBreak == false) {
			for (int i = 0; i < 43; i++) {
				for (int j = 0; j < 52; j++) {
					if (mapChip2D->GetFlag(i, j) == true) {
						bool flag = mapChip2D->GetFlag(i, j);
						int flag2 = mapChip2D->GetChipData(i, j)->GetCost();
						if (flag && (int)MapInfo::NONE == flag2 && bloodMapChip[i][j] == 0) {
							Vector2 pos = mapChip2D->GetChipPos(i, j);
							player_->Shot(scrollCamera_, { pos.x,pos.y });
							break;
						}
					}
				}
			}

			for (int i = 0; i < 43; i++) {
				for (int j = 0; j < 52; j++) {
					bloodMapChip[i][j] = 0;
				}
			}
			for (std::unique_ptr<Blood>& blood : player_->GetBloods()) {
				if (blood->GetState() == (int)Blood::State::idle) {
					Vector2 vec2 = { blood->GetPos().x / 64,blood->GetPos().y / 64 };
					bloodMapChip[(int)vec2.y][(int)vec2.x] = 1;
				}
			}
		}
		player_->Update(scrollCamera_);
		//scrollCamera_->Update(player_->GetSprite()->GetPosition());

		int bloodGauge = player_->GetBloodGauge();
		//						横幅(1090)を10で割った数,縦幅
		bloodGaugeSprite_->SetSize({ (float)1090 / player_->GetMaxBloodGauge() * bloodGauge,27 });							// 血量バーの大きさを変える
		for (int i = 0; i < 6; i++) {
			float u = player_->GetUltGaugeM(i);
			const float ultSpriteMaxSizeX = 36.0f; const float ultSpriteMaxSizeY = 336.0f;
			ultGaugeSprite_[i]->SetSize({ ultSpriteMaxSizeX,(ultSpriteMaxSizeY / player_->GetUltMaxGauge()) * -u });	// 体温バーの大きさを変える
		}

		//overheatSprite_->SetSize({ ultSpriteMaxSizeX,(ultSpriteMaxSizeY / player_->GetUltMaxGauge()) * -u });	// 体温バーの大きさを変える
		messageWindow_->Update(player_->GetPosition(), 32);
		if (messageWindow_->GetCountTarget() == L"ULT") {
			messageWindow_->SetCounter(player_->GetUltGauge());
		}
		else if (messageWindow_->GetCountTarget() == L"ENEMY") {
			//敵撃破カウントできる機構あったらいいね
		}
		else if (messageWindow_->GetCountTarget() == L"TIME") {
			messageWindow_->SetCounter((float)timer_->GetTimeRange());
		}

		if (!isTutorial_) {
			enemys_->Update(tower_->GetHP(), player_->GetPlayerHp(), scrollCamera_->GetPosition());
		}
	}

	marker_->Update(scrollCamera_->GetPosition());

	mapChip2D->Update(GetWorldMousePos());


	//if (player_->GetUltLevel() == 0) {
	//	overheatSprite_->SetColor({ 1.0f, 1.0f,1.0f });
	//}
	//else if (player_->GetUltLevel() == 1) {
	//	overheatSprite_->SetColor({ 1.0f, 1.0f,1.0f });
	//}
	//else if (player_->GetUltLevel() == 2) {
	//	overheatSprite_->SetColor({ 1.0f, 0.0f,1.0f });
	//}
	//else if (player_->GetUltLevel() == 3) {
	//	overheatSprite_->SetColor({ 0.5f, 0.5f,1.0f });
	//}
	//else if (player_->GetUltLevel() == 4) {
	//	overheatSprite_->SetColor({ 0.5f, 1.0f,0.5f });
	//}
	//else if (player_->GetUltLevel() == 5) {
	//	overheatSprite_->SetColor({ 0.5f, 0.5f,0.5f });
	//}

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
				int an = vampire->GetAnBloodType();
				if (an == blood->GetTemperature()) {
					blood->SetDead();
				}
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
				int an = basilisk->GetAnBloodType();
				if (an == blood->GetTemperature()) {
					blood->SetDead();
				}
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
				int an = rabbit->GetAnBloodType();
				if (an == blood->GetTemperature()) {
					blood->SetDead();
				}
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
			towerUIAnimationCount_++;
			SoundManager::GetIns()->PlaySE(SoundManager::SEKey::sekihiDamage, 0.1f);
		}
	}

	for (auto& basilisk : enemys_->GetBasiliskes())
	{
		bool isHit = Collision::HitCircle(basilisk->Getpos(), 32, tower_->GetPos(), 16);
		if (isHit)
		{
			tower_->OnCollision();
			basilisk->OnCollision();
			towerUIAnimationCount_++;
			SoundManager::GetIns()->PlaySE(SoundManager::SEKey::sekihiDamage, 0.1f);
		}
	}

	for (auto& rabbit : enemys_->GetRabbits())
	{
		bool isHit = Collision::HitCircle(rabbit->Getpos(), 32, tower_->GetPos(), 16);
		if (isHit)
		{
			tower_->OnCollision();
			rabbit->OnCollision();
			towerUIAnimationCount_++;
			SoundManager::GetIns()->PlaySE(SoundManager::SEKey::sekihiDamage, 0.1f);
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
	mapChip2D->Draw();
	marker_->Draw();
	enemys_->Draw();
	particle_->Draw();
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
	//text_->Draw("meiryo", "white", wstr1 + L"\n" + wstr2 + L"\n" + wstr3 + L"\n" + wstr4, textDrawRange);
	if (!pose_) {
		messageWindow_->TextMessageDraw();
	}

	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	//ポストエフェクト描画
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);

	//ポストエフェクトをかけないスプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	poseButton_->Draw();
	GameSprite1_->Draw();
	for (int i = 0; i < 6; i++) {
		ultGaugeSprite_[i]->Draw();
	}
	if (player_->GetUltState()) {
		//overheatSprite_->Draw();
	}
	GameSprite2_->Draw();
	//GameSprite3_->Draw();
	bloodGaugeSprite_->Draw();
	playerHp->Draw();
	reticleSprite_->Draw();
	// タワーの体力に合わせてUIが変わる
	towerUISprites_[towerUIAnimationCount_]->Draw();

	if (pose_) {
		poseBackButton_->Draw();
		titleButton_->Draw();
		manual_->Draw();
	}
	else {
		messageWindow_->SpriteDraw();
	}
	timer_->Draw();
	towerBreak_[towerBreakAnime_]->Draw();
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

	for (int32_t i = 0; i < towerUIAnimationMax; i++) {
		safe_delete(towerUISprites_[i]);
	}

	Sprite::SetCamera2D(nullptr);
}

void GameScene::HitEnemys()
{

}

Vector2 GameScene::GetWorldMousePos()
{
	Vector2 mousePos{};
	mousePos.x = MouseInput::GetIns()->ClientToPostEffect().x;
	mousePos.y = MouseInput::GetIns()->ClientToPostEffect().y;
	mousePos += scrollCamera_->GetPosition();
	return mousePos;
}

void GameScene::SceneChange()
{
	bool isOver = false;
	const float gameOverTime = 20.0f;
	if (tower_->GetHP() <= 0) {
		gameOverTimer_++;
		towerBreakAnimeTimer_++;
		for (int32_t i = 0; i < 4; i++) {
			towerBreak_[i]->SetPosition({ 640.0f, Easing::easeOutBounce((float)gameOverTimer_, gameOverTime, towerBreak_[i]->GetPosition().y, 360.0f) });
		}

		if (towerBreakAnimeTimer_ >= gameOverTime) {
			towerBreakAnime_ = (towerBreakAnime_ + 1) % 4;
			towerBreakAnimeTimer_ = 0;
		}
		if (gameOverTimer_ >= gameOverTime * 4) {
			isOver = true;
		}
	}

	if (pose_ && titleButton_->GetIsClick()) {
		SceneManager::SceneChange(SceneManager::SceneName::Title);
	}
	else if (enemys_->GetGameFlag() == 1)
	{
		SceneManager::SceneChange(SceneManager::SceneName::Result);
	}
	else if (isOver && !debugMuteki)
	{
		SceneManager::SceneChange(SceneManager::SceneName::Over);

	}
}

void GameScene::RoadPlayer()
{
	std::string line;
	Vector2 pos{};
	float rote;
	int32_t maxBlood[6] = {}, speed[6] = {}, hp = 0;
	std::stringstream stream;
	if (SceneManager::GetStageNo() != 0) {
		stream = ExternalFileLoader::GetIns()->ExternalFileOpen("player.txt");
	}
	else {
		stream = ExternalFileLoader::GetIns()->ExternalFileOpen("TutorialPlayer.txt");
	}

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
			line_stream >> maxBlood[0];
			line_stream >> maxBlood[1];
			line_stream >> maxBlood[2];
			line_stream >> maxBlood[3];
			line_stream >> maxBlood[4];
			line_stream >> maxBlood[5];
		}
		if (word.find("speed") == 0) {
			line_stream >> speed[0];
			line_stream >> speed[1];
			line_stream >> speed[2];
			line_stream >> speed[3];
			line_stream >> speed[4];
			line_stream >> speed[5];
		}
		if (word.find("hp") == 0) {
			line_stream >> hp;
		}
	}
	player_ = Player::Create(pos, rote, hp, maxBlood, speed);
}

