#include "Enemys.h"
#include "ImageManager.h"

#include "SafeDelete.h"

Enemys::Enemys()
{
}

Enemys::~Enemys()
{
	safe_delete(randCreate_);

}

Enemys* Enemys::Create()
{
	Enemys* enemys = new Enemys();
	enemys->enemyCreateTime = 200;
	enemys->randCreate_ = new RandCreate();
	enemys->enemyNumber_ = 0;
	enemys->deadCount = 0;
	enemys->gameFlag = 0;

	return enemys;
}

void Enemys::Update(int32_t towerHp, int playerHp, Vector2 camera)
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
	for (auto& vampire : Vampires_) {
		vampire->Update();
		vampire->WorldMarker(camera);
	}
	for (auto& basilisk : Basiliskes_) { 
		basilisk->Update(); 
		basilisk->WorldMarker(camera);
	}
	for (auto& rabbit : Rabbits_) {
		rabbit->Update();
		rabbit->WorldMarker(camera);
	}

	//血との当たり判定
	EnemyHitBlood();

	//砦との当たり判定
	//EnemyHitTower();

	//死亡処理
	EnemysDead();
}

void Enemys::EnemyCreate(const int phase)
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

void Enemys::EnemyHitBlood()
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



void Enemys::EnemyHitTower()
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

void Enemys::EnemysDead()
{
	Vampires_.remove_if([](std::unique_ptr<VampireEnemy>& vampire) {return vampire->GetDead();  });
	Basiliskes_.remove_if([](std::unique_ptr<BasiliskEnemy>& basilisk) {return basilisk->GetDead();  });
	Rabbits_.remove_if([](std::unique_ptr<RabbitEnemy>& rabbit) {return rabbit->GetDead();  });

}

void Enemys::Draw()
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
