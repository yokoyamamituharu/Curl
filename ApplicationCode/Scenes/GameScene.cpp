#include "GameScene.h"
#include "ExternalFileLoader.h"

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

	postEffectNo_ = PostEffect::NONE;

	blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);

	enemys_ = new Enemys();
	enemys_ = Enemys::Create();
	enemy_ = new Enemy();
	enemy_ = Enemy::Create();

	blood_ = Blood::Create({ 300,500 }, Blood::Temperature::solid);
	//player_ = Player::Create();
	RoadPlayer();
	bgSprite_ = Sprite::Create(UINT(ImageManager::ImageName::bgTexNumber), { 0,0 });
	int32_t towerHP = 10;
	tower_ = new Tower;
	tower_->Initialize(towerHP);
	scrollCamera_ = ScrollCamera::Create();
	Sprite::SetCamera(scrollCamera_);
}

void GameScene::Update()
{
	//blood_->Update();
	HitBloodAndEnemys();

	player_->Update(scrollCamera_);
	scrollCamera_->Update();
	if (KeyInput::GetIns()->TriggerKey(DIK_UP)) { blood_->Rising(); }
	if (KeyInput::GetIns()->TriggerKey(DIK_DOWN)) { blood_->Decrease(); }
	blood_->Update();


	//enemys_->Update(tower_->GetHP(), player_->GetPlayerHp());
	//enemy_->Update();

	//シーン切り替え
	SceneChange();
}

void GameScene::HitBloodAndEnemys()
{
	//enemy_1 = enemys_->GetEnemys();
	for (auto& enemy : enemys_->GetEnemys())
	{
		for (auto& blood : player_->GetBloods())
		{
			bool isHit = Collision::HitCircle(enemy->Getpos(), 32, blood->GetPos(), 16);

			if (isHit == TRUE)
			{
				enemy->SetBloadHitFlag(isHit);
				enemy->SetBloodType(blood->GetTemperature());
			}

		}

	}

	//enemys_->SetEnemys(enemy_1);

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
	//scrollCamera->Draw(player_->GetSprite());
	//blood_->Draw();
	enemys_->Draw();
	//enemy_->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	//テキスト描画範囲
	D2D1_RECT_F textDrawRange = { 0, 0, 500, 500 };
	text_->Draw("meiryo", "white", L"ゲームシーン\n左クリックでタイトルシーン\n右クリックでリザルトシーン", textDrawRange);
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();
}

void GameScene::Finalize()
{
	safe_delete(text_);
	safe_delete(blood_);
	//enemys_->Delete();
	safe_delete(enemys_);
	safe_delete(enemy_);
	safe_delete(player_);
	safe_delete(bgSprite_);
	safe_delete(tower_);
	safe_delete(scrollCamera_);
}

void GameScene::HitEnemys()
{

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

