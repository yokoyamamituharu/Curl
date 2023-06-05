#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy : public BaseEnemy
{

private:


public:
	~BasiliskEnemy();
	static std::unique_ptr<BasiliskEnemy> UniqueCreate();

	void Update();

	void Draw();

private: //定数
	//前向きアニメーション数
	static const int32_t frontAnimationCount = 6;
	//横向きアニメーション数
	static const int32_t besideAnimationCount = 2;
	//後ろ向きアニメーション数
	static const int32_t backAnimationCount = 6;

private: //メンバ変数

	bool moveFlag{};
	float moveAngle = 1.f;
};

