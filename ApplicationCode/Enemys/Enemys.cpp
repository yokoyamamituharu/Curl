#include "Enemys.h"
#include "ImageManager.h"
#include "Enemy.h"
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


	return enemys;
}

void Enemys::Update(int32_t towerHp, int playerHp)
{
	enemyCreateTime--;
	if ((towerHp > 0 || playerHp > 0) && enemyNumber_ < 72 && enemyCreateTime < 0)
	{
		EnemyCreate();
		enemyNumber_++;
		enemyCreateTime = randCreate_->getRandInt(10, 100);
	}

	for (auto& enemy : enemys3_)
	{
		enemy->Update();
	}
	for (auto& enemy : Vampires_)
	{
		enemy->Update();
	}
	for (auto& enemy : Basiliskes_)
	{
		enemy->Update();
	}
	for (auto& enemy : Rabbits_)
	{
		enemy->Update();
	}
	EnemyHitBlood();
	EnemyHitTower();
}

void Enemys::EnemyCreate()
{
	int temp = randCreate_->getRandInt(1, 6);

	if (temp == 1|| temp == 4)
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
	/*else
	{
		Rabbits_.push_back(RabbitEnemy::UniqueCreate());
	}*/
	//enemys3_.push_back(Enemy::UniqueCreate());
}

void Enemys::EnemyHitBlood()
{
	for (unique_ptr<Enemy>& enemy : enemys3_)
	{
		if (enemy->GetBloodHitFlag() == true)
		{
			if (enemy->GetBloodType() == enemy->GetHitBloodType())
			{
				enemy->SetDead(1);
				enemyNumber_--;
			}
			else if (enemy->GetBloodType() == enemy->GetAnBloodType())
			{
				enemy->SetMoveAddLength(2.f);
			}
			else
			{
				enemy->SetMoveAddLength(0.5f);
			}
		}
		else
		{
			enemy->SetMoveAddLength(1.f);
		}
	}
	enemys3_.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->GetDead();  });

	for (unique_ptr<VampireEnemy>& vampire : Vampires_)
	{
		if (vampire->GetBloodHitFlag() == true)
		{
			if (vampire->GetBloodType() == vampire->GetHitBloodType())
			{
				vampire->SetDead(TRUE);
				enemyNumber_--;
			}
			else if (vampire->GetBloodType() == vampire->GetAnBloodType())
			{
				vampire->SetMoveAddLength(2.f);
			}
			else
			{
				vampire->SetMoveAddLength(0.5f);
			}
		}
		else
		{
			vampire->SetMoveAddLength(1.f);
		}
	}
	Vampires_.remove_if([](std::unique_ptr<VampireEnemy>& vampire) {return vampire->GetDead();  });
	for (unique_ptr<BasiliskEnemy>& basilisk : Basiliskes_)
	{
		if (basilisk->GetBloodHitFlag() == true)
		{
			if (basilisk->GetBloodType() == basilisk->GetHitBloodType())
			{
				basilisk->SetDead(TRUE);
				enemyNumber_--;
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
	Basiliskes_.remove_if([](std::unique_ptr<BasiliskEnemy>& basilisk) {return basilisk->GetDead();  });
	for (unique_ptr<RabbitEnemy>& rabbit : Rabbits_)
	{
		if (rabbit->GetBloodHitFlag() == true)
		{
			if (rabbit->GetBloodType() == rabbit->GetHitBloodType())
			{
				rabbit->SetDead(TRUE);
				enemyNumber_--;
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
	Rabbits_.remove_if([](std::unique_ptr<RabbitEnemy>& rabbit) {return rabbit->GetDead();  });
}



void Enemys::EnemyHitTower()
{

	//for (auto& enemy : enemys3_)
	//{
	//	if (enemy->GetMoveLength() <= 5.f)
	//	{
	//		enemyNumber_--;
	//	}
	//}
	//enemys3_.remove_if([](unique_ptr<Enemy>& enemy1) {return enemy1->GetMoveLength() <= 5; });

	for (auto& vampire : Vampires_)
	{
		if (vampire->GetMoveLength() <= 5.f)
		{
			enemyNumber_--;
		}
	}
	Vampires_.remove_if([](unique_ptr<VampireEnemy>& vampire) {return vampire->GetMoveLength() <= 5; });
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

void Enemys::Draw()
{
	for (unique_ptr<Enemy>& enemy : enemys3_)
	{
		enemy->Draw();
	}

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
