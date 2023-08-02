#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy : public BaseEnemy
{

private:





public:
	~BasiliskEnemy();//削除
	static std::unique_ptr<BasiliskEnemy> UniqueCreate(Cell cell);//作成

	void Update();// 更新

	void Draw(bool isInvisible = false);//描画

private: //定数
	//前向きアニメーション数
	static const int32_t frontAnimationCount = 6;
	//横向きアニメーション数
	static const int32_t besideAnimationCount = 2;
	//後ろ向きアニメーション数
	static const int32_t backAnimationCount = 6;

	int useAnimation = 0;

	Cell dPos_ = { 0,0 };
	Cell gorl = { 0,0 };

	int chipSize = 64;

private: //メンバ変数

	bool moveFlag{};//左右どっちに回るかのフラグ
	float moveAngle = 1.f;//アングル加算値
};

