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
		enemys[i] = new Enemy();
		enemys[i]->sprite = Sprite::Create(type+3, {});
		enemys[i]->sprite->SetAnchorPoint({ 0.5f,0.5f });
		enemys[i]->enemyType = type;
		enemys[i]->moveLength = randCreate->getRandFloat(250,300);
		enemys[i]->angle = (float)i*10.f/*randCreate->getRandFloat(0.f, 359.f)*/;
		enemys[i]->pos.x = sin((enemys[i]->angle * DirectX::XM_PI) / 180) * enemys[i]->moveLength;
		enemys[i]->pos.y = cos((enemys[i]->angle * DirectX::XM_PI) / 180) * enemys[i]->moveLength;
		enemys[i]->pos.x = enemys[i]->pos.x + 640.f;
		enemys[i]->pos.y = enemys[i]->pos.y + 360.f;
		enemys[i]->sprite->SetPosition(enemys[i]->pos);
	}
	
}

void Enemys::Update()
{
	
	for (int i = 0; i < 36; i++)
	{
		enemys[i]->pos.x = sin((enemys[i]->angle * DirectX::XM_PI) / 180) * enemys[i]->moveLength;
		enemys[i]->pos.y = cos((enemys[i]->angle * DirectX::XM_PI) / 180) * enemys[i]->moveLength;
		enemys[i]->pos.x = enemys[i]->pos.x + 640.f;
		enemys[i]->pos.y = enemys[i]->pos.y + 360.f;
		enemys[i]->sprite->SetPosition(enemys[i]->pos);
	}
}

void Enemys::Draw()
{
	for (int i = 0; i < 36; i++)
	{
		enemys[i]->sprite->Draw();

	}
}
