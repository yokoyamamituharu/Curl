#include "Enemys.h"
#include "ImageManager.h"
#include "Enemy.h"

Enemys::Enemys()
{
}

Enemys::~Enemys()
{

}

Enemys* Enemys::Create()
{
	Enemys* enemys = new Enemys();
	enemys->enemyCreateTime = 200;

	for (int i = 0; i < 10; i++)
	{
		enemys->enemys3_.push_back(UniqueCreate(RandCreate::sGetRandInt()));

	}

	enemys->enemys3_.push_back(UniqueCreate());

	return nullptr;
}
