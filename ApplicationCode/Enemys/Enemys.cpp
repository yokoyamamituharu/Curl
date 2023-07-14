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
	//�������Ԃ̌��Y
	enemyCreateTime--;
	if (deadCount >= 30)gameFlag = TRUE;
	//�������Ԃ�0��������,�v���C���[��HP��1�ȏォ���ʂ�72�����̏ꍇ�G�𐶐�
	if ((towerHp > 0 || playerHp > 0) && enemyNumber_ < 72 && enemyCreateTime < 0)
	{
		//�G�𐶐�
		EnemyCreate(3);
		//�G�̑��ʂ����Z
		enemyNumber_++;
		//�������ԃ����_�����
		enemyCreateTime = randCreate_->getRandInt(10, 100);
	}

	
	//�G���ꂼ��̍X�V
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

	//���Ƃ̓����蔻��
	EnemyHitBlood();

	//�ԂƂ̓����蔻��
	//EnemyHitTower();

	//���S����
	EnemysDead();
}

void Enemys::EnemyCreate(const int phase)
{
	//�o�������ݒ�
	int temp = randCreate_->getRandInt(1, 6);

	//�t�F�[�Y1(���@���p�C�A)
	if (phase == 1) {
		Vampires_.push_back(VampireEnemy::UniqueCreate());
	}
	//�t�F�[�Y2�i���@���p�C�A�A�E�T�M�j
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
	//�t�F�[�Y3�i���@���p�C�A�A�E�T�M�A�o�W���X�N�j
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
		//���Ɠ������Ă���
		if (vampire->GetBloodHitFlag() == TRUE)
		{
			//���̃^�C�v����肩�ǂ���
			if (vampire->GetBloodType() == vampire->GetHitBloodType())
			{
				//�G�̎��S�t���O�𗧂Ă�
				vampire->OnCollision();
				//�G�̑��ʂ����炷
				enemyNumber_--;
				//���S�J�E���g
				deadCount++;
			}
			
			//���̃^�C�v�����ӂ��ǂ���
			else if (vampire->GetBloodType() == vampire->GetAnBloodType())
			{
				//�G�̋���
				vampire->SetMoveAddLength(2.f);
			}

			//���̃^�C�v���ǂ���ł��Ȃ�
			else
			{
				//�G�̎�̉�
				vampire->SetMoveAddLength(0.5f);
			}
		}
		//���Ɠ������Ă��Ȃ�
		else
		{
			//���̂܂�
			vampire->SetMoveAddLength(1.f);
		}
	}

	//���S�t���O�������Ă�����f���[�g
	//Vampires_.remove_if([](std::unique_ptr<VampireEnemy>& vampire) {return vampire->GetDead();  });

	//�ȉ�����
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
	//�ԂƂ̓����蔻��
	for (auto& vampire : Vampires_)
	{
		//�ԂƂ̋�����5.f�ȉ����ǂ���
		if (vampire->GetMoveLength() <= 5.f)
		{
			//�G�̑��ʌ��Z
			enemyNumber_--;
		}
	}
	//�ԂƂ̋�����5.f�ȉ���������f���[�g
	Vampires_.remove_if([](unique_ptr<VampireEnemy>& vampire) {return vampire->GetMoveLength() <= 5; });
	
	//�ȉ�����
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
