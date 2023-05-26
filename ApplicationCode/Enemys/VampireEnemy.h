#pragma once
#include"BaseEnemy.h"
#include<memory>
#include<list>
class VampireEnemy: public BaseEnemy
{
private:


public:
	~VampireEnemy();
	static std::unique_ptr<VampireEnemy> UniqueCreate();

	void Update();

	void Draw();

private:

};

