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
	if ((towerHp > 0 || playerHp > 0)&& enemyNumber_ < 72&& enemyCreateTime<0)
	{
		EnemyCreate();
		enemyNumber_++;
		enemyCreateTime = randCreate_->getRandInt(10,100);
	}

	for (auto& enemy : enemys3_)
	{
		enemy->Update();
	}
	EnemyHitBlood();
	EnemyHitTower();
}

void Enemys::EnemyCreate()
{
enemys3_.push_back(Enemy::UniqueCreate());
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
			else if(enemy->GetBloodType() == enemy->GetAnBloodType())
			{
				enemy->SetMoveAddLength(2);
			}
			else
			{
				enemy->SetMoveAddLength(0);
			}
		}
	}
	enemys3_.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->GetDead();  });

}

void Enemys::EnemyHitTower()
{

	for (auto& enemy : enemys3_)
	{
		if (enemy->GetMoveLength() <= 5)
		{
			enemyNumber_--;

		}
		
	}
	enemys3_.remove_if([](unique_ptr<Enemy>& enemy1) {return enemy1->GetMoveLength() <= 5; });

}

void Enemys::Draw()
{
	for (unique_ptr<Enemy>& enemy : enemys3_)
	{
		enemy->Draw();
	}
}
