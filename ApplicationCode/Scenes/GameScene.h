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
#include "ScrollCamera.h"

#include "Button.h"
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

	void RoadPlayer();

private: //メンバ変数
	//ポストエフェクト
	std::unique_ptr<PostEffect> postEffect_;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo_;
	//ライト
	std::unique_ptr<LightGroup> light_;
	//テキスト描画
	TextDraw* text_;

	Player* player_ = nullptr;
	Tower* tower_ = nullptr;
	Sprite* bgSprite_ = nullptr;
	Sprite* GameSprite1 = nullptr;
	Sprite* GameSprite2 = nullptr;
	Sprite* GameSprite3 = nullptr;
	std::unique_ptr<Sprite> bloodGaugeSprite_ = nullptr;
	
	Enemys* enemys_{};
	
	ScrollCamera* scrollCamera_ = nullptr;

	std::unique_ptr<Button> button_;
	std::unique_ptr<Button>	poseButton_;
	std::unique_ptr<Button>	poseBackButton_;
	std::unique_ptr<Button>	titleButton_;

	bool pose_ = false;
};

