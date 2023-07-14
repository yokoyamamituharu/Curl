#include "EnemyManager.h"
#include "ImageManager.h"
#include "ExternalFileLoader.h"
#include "SafeDelete.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	safe_delete(randCreate_);

}

EnemyManager* EnemyManager::Create()
{
	EnemyManager* enemys = new EnemyManager();
	enemys->enemyCreateTime = 200;
	enemys->randCreate_ = new RandCreate();
	enemys->enemyNumber_ = 0;
	enemys->deadCount = 0;
	enemys->gameFlag = 0;

	return enemys;
}

void EnemyManager::Update(int32_t towerHp, int playerHp)
{
	//生成時間の減産
	enemyCreateTime--;
	if (deadCount >= 30)gameFlag = TRUE;
	//生成時間が0未満かつ砦,プレイヤーのHPが1以上かつ総量が72未満の場合敵を生成
	if ((towerHp > 0 || playerHp > 0) && enemyNumber_ < 72 && enemyCreateTime < 0)
	{
		//敵を生成
		EnemyCreate(3);
		//敵の総量を加算
		enemyNumber_++;
		//発生時間ランダム代入
		enemyCreateTime = randCreate_->getRandInt(10, 100);
	}

	
	//敵せれぞれの更新
	for (auto& vampire : Vampires_)vampire->Update();
	for (auto& basilisk : Basiliskes_)basilisk->Update();
	for (auto& rabbit : Rabbits_)rabbit->Update();

	//血との当たり判定
	EnemyHitBlood();

	//砦との当たり判定
	//EnemyHitTower();

	//死亡処理
	EnemysDead();
}

void EnemyManager::EnemyCreate(const int phase)
{
	//出現乱数設定
	int temp = randCreate_->getRandInt(1, 6);

	//フェーズ1(ヴァンパイア)
	if (phase == 1) {
		Vampires_.push_back(VampireEnemy::UniqueCreate());
	}
	//フェーズ2（ヴァンパイア、ウサギ）
	else if (phase == 2) {
		if (temp == 1 || temp == 4 || temp == 3)
		{
			Vampires_.push_back(VampireEnemy::UniqueCreate());
		}
		if (temp == 2 || temp == 5 || temp == 6)
		{
			Rabbits_.push_back(RabbitEnemy::UniqueCreate());
		}
	}
	//フェーズ3（ヴァンパイア、ウサギ、バジリスク）
	else if (phase == 3) {
		if (temp == 1 || temp == 4)
		{
			Vampires_.push_back(VampireEnemy::UniqueCreate());
		}
		if (temp == 2 || temp == 5)
		{
			Basiliskes_.push_back(BasiliskEnemy::UniqueCreate());
		}
		if (temp == 3 || temp == 6)
		{
			Rabbits_.push_back(RabbitEnemy::UniqueCreate());
		}
	}
	/*else
	{
		Rabbits_.push_back(RabbitEnemy::UniqueCreate());
	}*/
	//enemys3_.push_back(Enemy::UniqueCreate());
}

void EnemyManager::EnemyHitBlood()
{

	for (unique_ptr<VampireEnemy>& vampire : Vampires_)
	{
		//血と当たっている
		if (vampire->GetBloodHitFlag() == TRUE)
		{
			//血のタイプが苦手かどうか
			if (vampire->GetBloodType() == vampire->GetHitBloodType())
			{
				//敵の死亡フラグを立てる
				vampire->OnCollision();
				//敵の総量を減らす
				enemyNumber_--;
				//死亡カウント
				deadCount++;
			}
			
			//血のタイプが得意かどうか
			else if (vampire->GetBloodType() == vampire->GetAnBloodType())
			{
				//敵の強化
				vampire->SetMoveAddLength(2.f);
			}

			//血のタイプがどちらでもない
			else
			{
				//敵の弱体化
				vampire->SetMoveAddLength(0.5f);
			}
		}
		//血と当たっていない
		else
		{
			//そのまま
			vampire->SetMoveAddLength(1.f);
		}
	}

	//死亡フラグが立っていたらデリート
	//Vampires_.remove_if([](std::unique_ptr<VampireEnemy>& vampire) {return vampire->GetDead();  });

	//以下同文
	for (unique_ptr<BasiliskEnemy>& basilisk : Basiliskes_)
	{
		if (basilisk->GetBloodHitFlag() == TRUE)
		{
			if (basilisk->GetBloodType() == basilisk->GetHitBloodType())
			{
				basilisk->OnCollision();
				enemyNumber_--;
				deadCount++;

			}
			else if (basilisk->GetBloodType() == basilisk->GetAnBloodType())
			{
				basilisk->SetMoveAddLength(2.f);
			}
			else
			{
				basilisk->SetMoveAddLength(0.5f);
			}
		}
		else
		{
			basilisk->SetMoveAddLength(1.f);
		}
	}
	//Basiliskes_.remove_if([](std::unique_ptr<BasiliskEnemy>& basilisk) {return basilisk->GetDead();  });
	for (unique_ptr<RabbitEnemy>& rabbit : Rabbits_)
	{
		if (rabbit->GetBloodHitFlag() == TRUE)
		{
			if (rabbit->GetBloodType() == rabbit->GetHitBloodType())
			{
				rabbit->OnCollision();
				enemyNumber_--;
				deadCount++;

			}
			else if (rabbit->GetBloodType() == rabbit->GetAnBloodType())
			{
				rabbit->SetMoveAddLength(2.f);
			}
			else
			{
				rabbit->SetMoveAddLength(0.5f);
			}
		}
		else
		{
			rabbit->SetMoveAddLength(1.f);
		}
	}
	//Rabbits_.remove_if([](std::unique_ptr<RabbitEnemy>& rabbit) {return rabbit->GetDead();  });
}



void EnemyManager::EnemyHitTower()
{
	//砦との当たり判定
	for (auto& vampire : Vampires_)
	{
		//砦との距離が5.f以下かどうか
		if (vampire->GetMoveLength() <= 5.f)
		{
			//敵の総量減算
			enemyNumber_--;
		}
	}
	//砦との距離が5.f以下だったらデリート
	Vampires_.remove_if([](unique_ptr<VampireEnemy>& vampire) {return vampire->GetMoveLength() <= 5; });
	
	//以下同文
	for (auto& basilisk : Basiliskes_)
	{
		if (basilisk->GetMoveLength() <= 5.f)
		{
			enemyNumber_--;
		}
	}
	Basiliskes_.remove_if([](unique_ptr<BasiliskEnemy>& basilisk) {return basilisk->GetMoveLength() <= 5; });
	for (auto& rabbit : Rabbits_)
	{
		if (rabbit->GetMoveLength() <= 5.f)
		{
			enemyNumber_--;
		}
	}
	Rabbits_.remove_if([](unique_ptr<RabbitEnemy>& rabbit) {return rabbit->GetMoveLength() <= 5; });

}

void EnemyManager::EnemysDead()
{
	Vampires_.remove_if([](std::unique_ptr<VampireEnemy>& vampire) {return vampire->GetDead();  });
	Basiliskes_.remove_if([](std::unique_ptr<BasiliskEnemy>& basilisk) {return basilisk->GetDead();  });
	Rabbits_.remove_if([](std::unique_ptr<RabbitEnemy>& rabbit) {return rabbit->GetDead();  });

}

void EnemyManager::EnemySpawnDataLoad()
{
	enemySpawnFileData_ = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage1_EnemySpawnData.csv");
	
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	Vector3 movePoint{};
	std::vector<Vector3> movePoints{};
	std::string type;
	float moveTime = 120.0f;//2[s]
	int32_t lifeTime = 240;//4[s]
	int32_t shotIntervalTime = 60;//1[s]
	int32_t hp = 1;
	int32_t waitTime = 0;
	bool isPos = false;
	bool isRot = false;
	bool isStyle = false;
	bool isMovePoint = false;

	//while (getline(enemyData_, line)) {
	//	std::istringstream line_stream(line);
	//	std::string word;
	//	//半角区切りで文字列を取得
	//	getline(line_stream, word, ' ');
	//	if (word == "#") {
	//		continue;
	//	}
	//	if (word == "Pos") {
	//		line_stream >> pos.x;
	//		line_stream >> pos.y;
	//		line_stream >> pos.z;
	//		isPos = true;
	//	}
	//	if (word == "Rot") {
	//		line_stream >> rot.x;
	//		line_stream >> rot.y;
	//		line_stream >> rot.z;
	//		isRot = true;
	//	}
	//	if (word == "Type") {
	//		line_stream >> type;
	//		isStyle = true;
	//	}
	//	if (word == "Move") {
	//		line_stream >> movePoint.x;
	//		line_stream >> movePoint.y;
	//		line_stream >> movePoint.z;
	//		movePoints.push_back(movePoint);
	//	}
	//	if (word == "End") {
	//		isMovePoint = true;
	//	}
	//	if (word == "MoveTime") {
	//		line_stream >> moveTime;
	//		//秒数換算なので60倍する
	//		moveTime *= 60.0f;
	//	}
	//	if (word == "LifeTime") {
	//		line_stream >> lifeTime;
	//		lifeTime *= 60;
	//	}
	//	if (word == "ShotCoolTime") {
	//		line_stream >> shotIntervalTime;
	//	}
	//	if (word == "Hp") {
	//		line_stream >> hp;
	//	}
	//	if (word == "Wait") {
	//		line_stream >> waitTime;
	//		//break;
	//	}

	//	if (isPos && isRot && isStyle) {
	//		EnemyData enemyData;
	//		enemyData.pos_ = pos;
	//		enemyData.rot_ = rot;
	//		enemyData.type_ = type;
	//		if (isMovePoint) {
	//			enemyData.movePoints_ = movePoints;
	//			movePoints.clear();
	//		}
	//		enemyData.moveTime_ = moveTime;
	//		enemyData.lifeTime_ = lifeTime;
	//		enemyData.shotInterval_ = shotIntervalTime;
	//		enemyData.hp_ = hp;
	//		enemyData.waitTime_ = waitTime;
	//		enemyDatas_.push_back(enemyData);

	//		isPos = false;
	//		isRot = false;
	//		isStyle = false;
	//		isMovePoint = false;
	//	}
	//}

	//it_ = enemyDatas_.begin();
}

void EnemyManager::Draw()
{
	for (unique_ptr<VampireEnemy>& vampire : Vampires_)
	{
		vampire->Draw();
	}

	for (unique_ptr<BasiliskEnemy>& basilisk : Basiliskes_)
	{
		basilisk->Draw();
	}

	for (unique_ptr<RabbitEnemy>& rabbit : Rabbits_)
	{
		rabbit->Draw();
	}
}
