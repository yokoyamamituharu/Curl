#pragma once
#include"BaseEnemy.h"
#include<memory>
#include<list>
class VampireEnemy: public BaseEnemy
{
private:
	
	
	
	

public:
	~VampireEnemy();//削除
	static std::unique_ptr<VampireEnemy> UniqueCreate();//作成

	void Update();// 更新

	void Draw();//描画

private: //定数
	//前向きアニメーション画像
	static const int32_t frontAnimationCount = 6;
	//横向きアニメーション画像
	static const int32_t besideAnimationCount = 4;
	//後ろ向きアニメーション画像
	static const int32_t backAnimationCount = 6;

	int useAnimation = 0;
};

