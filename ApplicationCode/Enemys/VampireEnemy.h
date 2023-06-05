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

private: //定数
	//前向きアニメーション画像
	static const int32_t frontAnimationCount = 6;
	//横向きアニメーション画像
	static const int32_t besideAnimationCount = 4;
	//後ろ向きアニメーション画像
	static const int32_t backAnimationCount = 6;

};

