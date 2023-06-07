#pragma once
#include "BaseEnemy.h"
class BasiliskEnemy : public BaseEnemy
{

private:
	
	
	
	

public:
	~BasiliskEnemy();//削除
	static std::unique_ptr<BasiliskEnemy> UniqueCreate();//作成

	void Update();// 更新

	void Draw();//描画

private: //定数
	//前向きアニメーション数
	static const int32_t frontAnimationCount = 6;
	//横向きアニメーション数
	static const int32_t besideAnimationCount = 2;
	//後ろ向きアニメーション数
	static const int32_t backAnimationCount = 6;

private: //メンバ変数

	bool moveFlag{};//左右どっちに回るかのフラグ
	float moveAngle = 1.f;//アングル加算値
};

