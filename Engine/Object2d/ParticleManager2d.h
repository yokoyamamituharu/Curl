#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include <forward_list>

class ParticleManager2d
{
public: //構造体
	struct Particle2d {
		//座標
		Vector2 pos_;
		//速度ベクトル
		Vector2 velocity_;
		//加速度
		Vector2 accel_;
		//色
		Vector3 color_;
		//アルファ値
		float alpha_;
		//初期パラメータ
		Vector3 start_Color_;
		float start_Size_;
		float start_Rot_;
		float start_Alpha_;
		//最終パラメータ
		Vector3 end_Color_;
		float end_Size_;
		float end_Rot_;
		float end_Alpha_;
		//現在フレーム
		int32_t nowFrame_;
		//最終フレーム
		int32_t endFrame_;
		//パーティクル画像
		std::unique_ptr<Sprite> particle_;
	};

public: //静的メンバ関数
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	//static ParticleManager2d* Create();
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	//static std::unique_ptr<ParticleManager2d> UniquePtrCreate();
	/// <summary>
	/// パーティクル生成
	/// </summary>
	/// <returns>インスタンス</returns>
	//static std::unique_ptr<Particle2d> ParticleCreate();

public: //メンバ関数
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル追加
	/// </summary>
	/// <param name="particle">パーティクル</param>
	void Add(const Particle2d& particle);

private: //メンバ変数
	//パーティクルリスト
	std::forward_list<Particle2d> particleList_;
};