#pragma once
#include <DirectXMath.h>
#include "Vector2.h"
class Sprite;

class ScrollCamera
{
public:
	ScrollCamera() = default;
	~ScrollCamera() = default;

	static ScrollCamera* Create();

	void Update(Vector2  adulationTarget = {});

	void SetPosition(Vector2 pos) { this->pos = pos; }

	Vector2 GetPosition() { return pos; }

private:

private:
	Vector2 pos{};
};