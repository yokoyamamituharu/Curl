#include "Enemys.h"
#include "ImageManager.h"

void Enemys::Initialize()
{
	randCreate = new RandCreate();
	randCreate->Ins();
	keyInput = KeyInput::GetIns();
	
	for (int i = 0; i < 36; i++)
	{
		int type = randCreate->getRandInt(1, 3);
		enemys_[i] = new Enemy();
		enemys_[i]->sprite = Sprite::Create(type+3, {});
		enemys_[i]->sprite->SetAnchorPoint({ 0.5f,0.5f });
		enemys_[i]->enemyType = type;
		enemys_[i]->moveLength = randCreate->getRandFloat(250,300);
		enemys_[i]->angle = (float)i*10.f/*randCreate->getRandFloat(0.f, 359.f)*/;
		enemys_[i]->pos.x = sin((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.y = cos((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.x = enemys_[i]->pos.x + 640.f;
		enemys_[i]->pos.y = enemys_[i]->pos.y + 360.f;
		enemys_[i]->sprite->SetPosition(enemys_[i]->pos);
	}
	
}

void Enemys::Update()
{
	
	for (int i = 0; i < 36; i++)
	{
		enemys_[i]->pos.x = sin((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.y = cos((enemys_[i]->angle * DirectX::XM_PI) / 180) * enemys_[i]->moveLength;
		enemys_[i]->pos.x = enemys_[i]->pos.x + 640.f;
		enemys_[i]->pos.y = enemys_[i]->pos.y + 360.f;
		enemys_[i]->sprite->SetPosition(enemys_[i]->pos);
	}
}

void Enemys::Draw()
{
	for (int i = 0; i < 36; i++)
	{
		enemys_[i]->sprite->Draw();

	}
}
