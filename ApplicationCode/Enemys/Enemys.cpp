#include "Enemys.h"
#include "ImageManager.h"

void Enemys::Initialize()
{
	randCreate_ = new RandCreate();
	randCreate_->Ins();
	keyInput_ = KeyInput::GetIns();
	
	////¶¬‚Æ‰Šú‰»
	//unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
	//
	//
	////’e‚ğ“o˜^
	//enemys3_.push_back(move(newEnemy));

	for (int i = 0; i < 36; i++)
	{
		unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
		int type = randCreate_->getRandInt(1, 3);
		newEnemy->sprite = Sprite::Create(type + 3, {});
		newEnemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
		newEnemy->enemyType = type;
		newEnemy->moveLength = randCreate_->getRandFloat(250, 300);
		newEnemy->angle = (float)i * 10.f/*randCreate->getRandFloat(0.f, 359.f)*/;
		newEnemy->pos.x = sin((newEnemy->angle * DirectX::XM_PI) / 180) * newEnemy->moveLength;
		newEnemy->pos.y = cos((newEnemy->angle * DirectX::XM_PI) / 180) * newEnemy->moveLength;
		newEnemy->pos.x = newEnemy->pos.x + 640.f;
		newEnemy->pos.y = newEnemy->pos.y + 360.f;
		newEnemy->sprite->SetPosition(newEnemy->pos);
		//’e‚ğ“o˜^
		enemys3_.push_back(move(newEnemy));
		
		
	}
	//for (int i = 0; i < 36; i++)
	//{
	//	int type = randCreate_->getRandInt(1, 3);
	//	enemys_[i] = new Enemy();
	//	enemys_[i]->sprite = Sprite::Create(type+3, {});
	//	enemys_[i]->sprite->SetAnchorPoint({ 0.5f,0.5f });
	//	enemys_[i]->enemyType = type;
	//	enemys_[i]->moveLength = randCreate_->getRandFloat(250,300);
	//	enemys_[i]->angle = (float)i*10.f/*randCreate->getRandFloat(0.f, 359.f)*/;
	//	enemys_[i]->pos.x = sin((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
	//	enemys_[i]->pos.y = cos((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
	//	enemys_[i]->pos.x = enemys_[i]->pos.x + 640.f;
	//	enemys_[i]->pos.y = enemys_[i]->pos.y + 360.f;
	//	enemys_[i]->sprite->SetPosition(enemys_[i]->pos);
	//}
	
}

void Enemys::Update()
{

	for (unique_ptr<Enemy>& enemy : enemys3_)
	{
		enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
		enemy->pos.y = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
		enemy->pos.x = enemy->pos.x + 640.f;
		enemy->pos.y = enemy->pos.y + 360.f;
		enemy->sprite->SetPosition(enemy->pos);
		//enemy->sprite
	}
	if (keyInput_->TriggerKey(DIK_SPACE))
	{
		for (unique_ptr<Enemy>& enemy : enemys3_)
		{
			if (enemy->bloodHitFlag == 0)
			{
				enemy->bloodHitFlag = 1;
			}

			//enemy->sprite
		}
		enemys3_.remove_if([](unique_ptr<Enemy>& enemy) {return enemy->bloodHitFlag == true; });

	}
	
	if (keyInput_->TriggerKey(DIK_Q))
	{
		for (int i = 0; i < 36; i++)
		{
			unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
			int type = randCreate_->getRandInt(1, 3);
			newEnemy->sprite = Sprite::Create(type + 3, {});
			newEnemy->sprite->SetAnchorPoint({ 0.5f,0.5f });
			newEnemy->enemyType = type;
			newEnemy->moveLength = randCreate_->getRandFloat(250, 300);
			newEnemy->angle = (float)i * 10.f/*randCreate->getRandFloat(0.f, 359.f)*/;
			newEnemy->pos.x = sin((newEnemy->angle * DirectX::XM_PI) / 180) * newEnemy->moveLength;
			newEnemy->pos.y = cos((newEnemy->angle * DirectX::XM_PI) / 180) * newEnemy->moveLength;
			newEnemy->pos.x = newEnemy->pos.x + 640.f;
			newEnemy->pos.y = newEnemy->pos.y + 360.f;
			newEnemy->sprite->SetPosition(newEnemy->pos);
			//’e‚ğ“o˜^
			enemys3_.push_back(move(newEnemy));


		}
	}
	/*for (int i = 0; i < 36; i++)
	{
		enemys_[i]->pos.x = sin((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.y = cos((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.x = enemys_[i]->pos.x + 640.f;
		enemys_[i]->pos.y = enemys_[i]->pos.y + 360.f;
		enemys_[i]->sprite->SetPosition(enemys_[i]->pos);
	}*/
}

void Enemys::Draw()
{
	for (unique_ptr<Enemy>& enemy : enemys3_)
	{
		enemy->sprite->Draw();
		//enemy->sprite
	}
	/*for (int i = 0; i < 36; i++)
	{
		enemys_[i]->sprite->Draw();

	}*/
}

void Enemys::Delete()
{
	/*for (int i = 0; i < 36; i++)
	{
		delete enemys_[i]->sprite;

	}
	*/

}

Enemys::~Enemys()
{
	
}

Enemys::Enemy::~Enemy()
{
	delete sprite;

}
