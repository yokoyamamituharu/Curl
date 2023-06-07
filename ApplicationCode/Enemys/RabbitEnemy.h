#pragma once
#include "BaseEnemy.h"
class RabbitEnemy :public BaseEnemy
{
private:
	
	
	
	

public:
	~RabbitEnemy();//削除
	static std::unique_ptr<RabbitEnemy> UniqueCreate();//作成

	void Update();// 更新

	int BloodHit(int num);

	void Draw();//描画

private: //定数
	//前向きアニメーション画像
	static const int32_t frontAnimationCount = 3;
	//横向きアニメーション画像
	static const int32_t besideAnimationCount = 3;
	//後ろ向きアニメーション画像
	static const int32_t backAnimationCount = 3;

	int useAnimation = 0;
};

