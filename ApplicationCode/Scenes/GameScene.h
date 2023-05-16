#pragma once
#include "BaseScene.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Object3d.h"
#include "Vector3.h"
#include "Camera.h"
#include "MouseInput.h"
#include "Easing.h"
#include "Shapes.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "DebugText.h"
#include "MotionMath.h"
#include "SceneManager.h"
#include "TextDraw.h"
#include "JsonLoader.h"
#include"Enemys.h"

#include "Blood.h"
#include "Player.h"
#include "Tower.h"
#include "Enemy.h"

#include"Collision.h"
class GameScene : public BaseScene
{
public: //メンバ関数
	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 血と敵の当たり判定
	/// </summary>
	void HitBloodAndEnemys();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	void HitEnemys();

private: //メンバ関数
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //メンバ変数
	//ポストエフェクト
	std::unique_ptr<PostEffect> postEffect_;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo_;
	//地面
	std::unique_ptr<Object3d> ground_;
	//ライト
	std::unique_ptr<LightGroup> light_;
	//テキスト描画
	TextDraw* text_;

	Blood* blood_ = nullptr;
	Player* player_ = nullptr;
	Tower* tower_ = nullptr;
	Sprite* bgSprite_ = nullptr;
	
	Enemy* enemy_{};

	Enemys* enemys_{};
	list<unique_ptr<Enemy>> enemy_1;
};

