#pragma once
#include <DirectXMath.h>
#include"RandCreate.h"
#include "Sprite.h"
#include "KeyInput.h"
#include <memory>
#include <list>

#include "VampireEnemy.h"
#include "BasiliskEnemy.h"
#include "RabbitEnemy.h"
#include "Vector2.h"
#include <sstream>

using namespace std;

class EnemyManager
{
private:

public: //�\����

	struct EnemySpawnData {
		Vector2 spawnPoint_; //�o���ꏊ
		std::string enemyType_; //�G�^�C�v
		int32_t waitTime_; //�o���ҋ@����
	};

public:

	EnemyManager();
	~EnemyManager();

	static EnemyManager* Create();

	void Update(int32_t towerHp,int playerHp,Vector2 camera);

	void EnemyCreate(const int phase);

	void EnemyHitBlood();

	void EnemyHitTower();

	void EnemysDead();

	bool GetGameFlag() { return gameFlag; }

	list<unique_ptr<VampireEnemy>>& GetVampires() { return Vampires_; }
	list<unique_ptr<BasiliskEnemy>>& GetBasiliskes() { return Basiliskes_; }
	list<unique_ptr<RabbitEnemy>>& GetRabbits() { return Rabbits_; }
	/// <summary>
	/// �|�[�Y�t���O���Z�b�g
	/// </summary>
	/// <param name="isPause">�|�[�Y�t���O</param>
	void SetPause(bool isPause) { isPause_ = isPause; }
	/// <summary>
	/// �G�X�|�[���f�[�^�ǂݍ���
	/// </summary>
	void EnemySpawnDataLoad(const std::string& fileName);
	/// <summary>
	/// �G�X�|�[������
	/// </summary>
	void EnemySpawnDataUpdate();
	//void SetEnemys(list<unique_ptr<Enemy>> enemys) { this->enemys3_ = move(enemys); };
	void Draw();

private:
	
	int enemyNumber_{};//�o�����Ă���G�̑���
	int enemyCreateTime{};//��������
	RandCreate* randCreate_{};//�����_��
	KeyInput* keyInput_{};

	//unique_ptr<Enemy> enemys2_{};
	
	list<unique_ptr<VampireEnemy>> Vampires_{};
	list<unique_ptr<BasiliskEnemy>> Basiliskes_{};
	list<unique_ptr<RabbitEnemy>> Rabbits_{};

	list<EnemySpawnData> enemySpawnData_; //�G�o���f�[�^
	int32_t waitTimer_ = 500; //�o���ҋ@�^�C�}�[
	std::stringstream enemySpawnFileData_; //�G�o���f�[�^�i�[�p������
	std::list<EnemySpawnData>::iterator it_; //�C�e���[�^

	bool isWait_; //�ҋ@�t���O
	bool isPause_; //�|�[�Y���t���O

	int deadCount = 0;
	bool gameFlag = 0;

};

