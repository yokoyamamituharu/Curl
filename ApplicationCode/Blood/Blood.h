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

	void Update();

	void Rising();

	void Decrease();

	void Draw();

private:

public:

private:
	int state = NONE;
	DirectX::XMFLOAT2 position = { 0,0 };
	std::map<int, Sprite*> sprites;
};