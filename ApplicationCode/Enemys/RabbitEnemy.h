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

private: //定数
	//前向きアニメーション画像
	static const int32_t frontAnimationCount = 3;
	//横向きアニメーション画像
	static const int32_t besideAnimationCount = 3;
	//後ろ向きアニメーション画像
	static const int32_t backAnimationCount = 3;
};

