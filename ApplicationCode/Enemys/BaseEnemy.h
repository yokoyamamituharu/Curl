#pragma once
#include<array>
#include<DirectXMath.h>
#include <vector>
#include"Vector2.h"
#include"Sprite.h"
#include "ImageManager.h"
#include"..\AStar.h"

class BaseEnemy
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMVECTOR = DirectX::XMVECTOR;
	

public:

	enum EnemyType
	{
		vampire = 7,//個体
		basilisk,//液体
		rabbit,//気体
	};
	enum BloodState //血のタイプ
	{
		NONE_1,
		solid_1,
		liquid_1,
		gas_1
	};

	enum AnimationType 
	{
		front,
		rightSide,
		back,
		ReftSide,
	};
public:
	virtual ~BaseEnemy() {};//デリート

	XMFLOAT2 Getpos() { return pos; }//座標取得

	void SetMoveAddLength(float moveAddLength_) { this->moveAddLength = moveAddLength_; }//加算距離代入
	float GetMoveAddLength() { return moveAddLength; }//加算距離取得

	void SetMoveLength(float moveLength_) { this->moveLength = moveLength_; }//距離代入
	float GetMoveLength() { return moveLength; }//距離取得

	void SetBloodType(int bloodTipe_) { this->BloodType = bloodTipe_; }//血のタイプ代入
	int GetBloodType() { return BloodType; }//血のタイプ取得

	void SetHitBloodType(int hitBloodType_) { this->hitBloodType = hitBloodType_; }//苦手な血のタイプ代入
	int GetHitBloodType() { return hitBloodType; }//苦手な血のタイプ取得

	void SetAnBloodType(int anBloodType_) { this->anBloodType = anBloodType_; }//得意な血のタイプ代入
	int GetAnBloodType() { return anBloodType; }//得意な血のタイプ習得

	void SetBloadHitFlag(int bloodHitFlag_) { this->bloodHitFlag = bloodHitFlag_; }//血の当たり判定代入
	bool GetBloodHitFlag() { return bloodHitFlag; }//血の当たり判定取得

	void SetTowerHitFlag(int towerHitFlag_) { this->towerHitFlag = towerHitFlag_; }//守られている砦の当たり判定代入
	bool GetTowerHitFlag() { return towerHitFlag; }//守られている砦の当たり判定取得

	void SetDead(bool dead_) { this->dead = dead_; }//死亡フラグ代入
	bool GetDead() { return dead; }//死亡フラグ取得

	void SetMovePoint(XMFLOAT2 pos) { this->movePoint = pos; }//守られている砦座標代入
	XMFLOAT2 GetMovePoint() { return movePoint; }//守られている砦座標取得

	void OnCollision() { dead = true; }

	virtual	void Update() = 0;//更新

	//void Create(int type);

	virtual void Draw(bool makerFlag = true) = 0;//描画

	void WorldMarker(XMFLOAT2 camera);

protected: //静的メンバ関数

	/// <summary>
	/// 敵画像生成
	/// </summary>
	/// <param name="imageName">画像名</param>
	/// <param name="animationCount">アニメーション数</param>
	/// <param name="enemyPos">敵座標</param>
	/// <returns>アニメーションスプライト</returns>
	static std::vector<Sprite*> SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& enemyPos);

protected: //定数
	//アニメーション時間
	static const int32_t animationTime = 10;

protected:
	std::vector<Sprite*> frontSprites_;
	std::vector<Sprite*> besideSprites_;
	std::vector<Sprite*> backSprites_;

	XMFLOAT2 pos{};//座標

	float angle{};//角度
	float moveLength{};//距離
	float moveAddLength = 1;//加算距離

	int BloodType{};//血のタイプ
	int hitBloodType{};//苦手の血のタイプ
	int anBloodType{};//得意の血のタイプ

	bool bloodHitFlag{};//血との当たり判定フラグ
	bool towerHitFlag{};//砦との当たり判定フラグ
	bool dead{};//

	bool minWidthFlag{};
	bool minHeightFlag{};
	bool maxWidthFlag{};
	bool maxHeightFlag{};


	
	std::list<Cell>route;
	std::array<float, 360> maxAngle;//角度最大値
	std::array<float, 0> minAngle;//角度最小値

	//画面外にいるときに画面内に出すマーカー
	Sprite* markerSprite_ = nullptr;
	XMVECTOR markerAdd{};
	float markerLength = 1;
	XMFLOAT2 markerPos_{};
	float markerAngle{};
	bool isMarker_ = false;
	bool isRight_ = false;
	bool isLeft_ = false;
	bool isUp_ = false;
	bool isDown_ = false;

	//移動先座標
	XMFLOAT2 movePoint = { 640.f,360.f };
	//アニメーションタイマー
	int32_t animationTimer_ = 0;
	//前向きアニメーションカウンター
	int32_t frontAnimationCounter_ = 0;
	//横向きアニメーションカウンター
	int32_t besideAnimationCounter_ = 0;
	//後ろ向きアニメーションカウンター
	int32_t backAnimationCounter_ = 0;
};

