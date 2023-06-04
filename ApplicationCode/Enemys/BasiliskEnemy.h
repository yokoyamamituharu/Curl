#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy :public BaseEnemy
{

private:


public:
	~BasiliskEnemy();
	static std::unique_ptr<BasiliskEnemy> UniqueCreate();

	void Update();

	void Draw();

private:
	bool moveFlag{};
	float moveAngle = 1.f;
};

