#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
class Blood
{
public:
	enum STATE {
		NONE,
		solid,
		liquid,
		gas
	};

	Blood();

	~Blood();

	static Blood* Create(DirectX::XMFLOAT2 position, STATE state);
	
	static std::unique_ptr<Blood> UniquePtrCreate(DirectX::XMFLOAT2 position, STATE state,DirectX::XMFLOAT2 vec);

	/// <summary>
	/// 
	/// </summary>
	void Update();

	/// <summary>
	/// â∑ìxÇè„è∏Ç≥ÇπÇÈ
	/// </summary>
	void Rising();

	/// <summary>
	/// â∑ìxÇå∏è≠Ç≥ÇπÇÈ
	/// </summary>
	void Decrease();

	void Draw();

	bool GetDead();

private:

public:

private:
	int state_ = NONE;
	DirectX::XMFLOAT2 position_{};
	DirectX::XMFLOAT2 vec_{};
	std::map<int, Sprite*> sprites_;
	int deadTimer = 100;
	bool isDead = false;
};