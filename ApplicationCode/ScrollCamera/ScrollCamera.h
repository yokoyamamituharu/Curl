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
	/// �X�N���[�����l�������ꍇ�̉�ʒ[���W
	/// </summary>
	/// <returns>�E��</returns>
	static Vector2 GetMinScreenEdge();
	/// <summary>
	/// �X�N���[�����l�������ꍇ�̉�ʒ[���W
	/// </summary>
	/// <returns>����</returns>
	static Vector2 GetMaxScreenEdge();

public:
	static const Vector2 minPos;
	static const Vector2 maxPos;

private:

private:
	Vector2 pos{};
};