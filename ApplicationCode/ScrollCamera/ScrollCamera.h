#pragma once
#include <DirectXMath.h>
#include "Vector2.h"
class Sprite;

class ScrollCamera
{
public:
	ScrollCamera() = default;
	~ScrollCamera();

	static ScrollCamera* Create();

	void Update(Vector2  adulationTarget = {});

	void SetPosition(Vector2 pos) { this->pos = pos; }

	Vector2 GetPosition() { return pos; }	
	
	/// <summary>
	/// スクロールを考慮した場合の画面端座標
	/// </summary>
	/// <returns>右上</returns>
	static Vector2 GetMinScreenEdge();
	/// <summary>
	/// スクロールを考慮した場合の画面端座標
	/// </summary>
	/// <returns>左下</returns>
	static Vector2 GetMaxScreenEdge();

public:
	static const Vector2 minPos;
	static const Vector2 maxPos;

private:

private:
	Vector2 pos{};
};