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
	for (auto& vampire : Vampires_)vampire->Update();
	for (auto& basilisk : Basiliskes_)basilisk->Update();
	for (auto& rabbit : Rabbits_)rabbit->Update();

	//���Ƃ̓����蔻��
	EnemyHitBlood();

	//�ԂƂ̓����蔻��
	//EnemyHitTower();

	//���S����
	EnemysDead();
}

void EnemyManager::EnemyCreate(const int phase)
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

void EnemyManager::EnemyHitBlood()
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



void EnemyManager::EnemyHitTower()
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
	//	//���p��؂�ŕ�������擾
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
	//		//�b�����Z�Ȃ̂�60�{����
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
