#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::HitCircle(XMFLOAT2 pos1, float radius1, XMFLOAT2 pos2, float radius2)
{
	float temp = sqrtf(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));

	return temp < radius1 + radius2;
}

DirectX::XMFLOAT2 Collision::HitCrossWindows(XMFLOAT2 enemyPos, int flag)
{
	if (enemyPos.x <= -32.f || enemyPos.x >= (float)WinApp::window_width + 32.f)
	{

	}
}

bool Collision::CrossLine(XMFLOAT2 pos1, XMFLOAT2 pos2, XMFLOAT2 pos3, XMFLOAT2 pos4)
{
	//頂点A(pos1) - 頂点B(pos3)
	//頂点C(pos2) - 頂点D(pos4)

	bool ABFlag;
	bool cdFlag;
	float s;
	float t;

	s = ((pos3.x - pos1.x) * (pos2.y - pos1.y))
		- ((pos2.x - pos1.x) * (pos3.y - pos1.y));
	t = ((pos3.x - pos1.x) * (pos4.y - pos1.y))
		- ((pos4.x - pos1.x) * (pos3.y - pos1.y));
	if (s * t > 0)
	{
		ABFlag = false;
	}
	else
	{
		ABFlag = true;
	}
	s = ((pos2.x - pos4.x) * (pos1.y - pos2.y))
		- ((pos2.y - pos4.y) * (pos1.x - pos2.x));
	t = ((pos2.x - pos4.x) * (pos3.y - pos2.y))
		- ((pos2.y - pos4.y) * (pos3.x - pos2.x));
	if (s * t > 0)
	{
		cdFlag = false;
	}
	else
	{
		cdFlag = true;
	}

	if (ABFlag == true && cdFlag == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DirectX::XMFLOAT2 Collision::CrossLinePoint(XMFLOAT2 pos1, XMFLOAT2 pos2, XMFLOAT2 pos3, XMFLOAT2 pos4)
{
	//頂点A(pos1) - 頂点B(pos3)
	//頂点C(pos2) - 頂点D(pos4)
	//とした時、交点(x, y)は、
	//s₁ = { (x₄ - x₂) * (y₁ - y₂) - (y₄ - y₂) * (x₁ - x₂) } / 2.0
	//s₂ = { (x₄ - x₂) * (y₂ - y₃) - (y₄ - y₂) * (x₂ - x₃) } / 2.0
	//x = x₁ + (x₃ - x₁) * s₁ / (s₁ + s₂)
	//y = y₁ + (y₃ - y₁) * s₁ / (s₁ + s₂)

	float s1 = (
		(pos4.x - pos2.x) * (pos1.y - pos2.y) -
		(pos4.y - pos2.y) * (pos1.x - pos2.x)) / 2.f;

	float s2 = (
		(pos4.x - pos2.x) * (pos3.y - pos2.y) -
		(pos4.y - pos2.y) * (pos3.x - pos2.x)) / 2.f;

	XMFLOAT2 temp{};
	temp.x = pos1.x + (pos3.x - pos1.x) * s1 / (s1 + s2);
	temp.y = pos1.y + (pos3.y - pos1.y) * s1 / (s1 + s2);

	return temp;
}

bool Collision::OBJSphereCollision(Object3d* object1, Object3d* object2, float objScale1, float objScale2) {
	object1Pos = object1->GetMatWorld().r[3];

	object2Pos = object2->GetMatWorld().r[3];

	objectPosTotal = (object2Pos.x - object1Pos.x) * (object2Pos.x - object1Pos.x) + (object2Pos.y - object1Pos.y) * (object2Pos.y - object1Pos.y) + (object2Pos.z - object1Pos.z) * (object2Pos.z - object1Pos.z);
	objectScaleTotal = (objScale1 + objScale2) * (objScale1 + objScale2);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}