#pragma once
#include "BaseScene.h"
#include "Button.h"
#include "PostEffect.h"

class SelectScene : public BaseScene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

private: //仮想メンバ関数
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange() override;

private: //メンバ変数
	//ポストエフェクト
	std::unique_ptr<PostEffect> postEffect_;
	//チュートリアルボタン
	std::unique_ptr<Button> tutorial_;
	//ステージ1ボタン
	std::unique_ptr<Button> stage1_;
};

