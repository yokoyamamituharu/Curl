#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::HitCircle(XMFLOAT2 pos1, float radius1, XMFLOAT2 pos2, float radius2)
{
	float temp = sqrtf(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos1.y, 2));

	return temp < radius1 + radius2;
}

bool Collision::OBJSphereCollision(Object3d* object1, Object3d* object2, float objScale1, float objScale2) {
	object1Pos = object1->GetMatWorld().r[3];

	object2Pos = object2->GetMatWorld().r[3];

	objectPosTotal = (object2Pos.x - object1Pos.x) * (object2Pos.x - object1Pos.x) + (object2Pos.y - object1Pos.y) * (object2Pos.y - object1Pos.y) + (object2Pos.z - object1Pos.z) * (object2Pos.z - object1Pos.z);
	objectScaleTotal = (objScale1 + objScale2) * (objScale1 + objScale2);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}