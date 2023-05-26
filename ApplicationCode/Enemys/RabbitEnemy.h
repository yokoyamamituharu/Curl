#pragma once
#include "BaseEnemy.h"
class RabbitEnemy :public BaseEnemy
{
private:


public:
	~RabbitEnemy();
	static std::unique_ptr<RabbitEnemy> UniqueCreate();

	void Update();

	int BloodHit(int num);

	void Draw();

private:
	
};

