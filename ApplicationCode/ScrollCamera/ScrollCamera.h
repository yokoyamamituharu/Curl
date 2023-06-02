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

	void Update();

	void SetPosition(Vector2 pos) { this->pos = pos; }

	Vector2 GetPosition() { return pos; }

	void Draw(Sprite* sprite);
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:	
	Vector2 pos{};
};