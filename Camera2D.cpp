#include "Camera2D.h"

using namespace DirectX;

XMMATRIX Camera2D::matView{};
XMMATRIX Camera2D::matProjection{};
XMMATRIX Camera2D::matWorld{};
XMMATRIX Camera2D::matViewPort{};
XMFLOAT3 Camera2D::eye = { 0, 0.0f, 0.0f };
XMFLOAT3 Camera2D::target = { 0, 0,1 };
XMFLOAT3 Camera2D::up = { 0, 1, 0 };
XMMATRIX Camera2D::matBillboard = XMMatrixIdentity();
XMMATRIX Camera2D::matBillboardY = XMMatrixIdentity();
bool Camera2D::isMatWorldCalc = false;

void Camera2D::InitializeCamera(int32_t window_width, int32_t window_height)
{
	// ビュー行列の生成
	UpdateViewMatrix();

	// 透視投影による射影行列の生成
	matProjection = XMMatrixOrthographicOffCenterLH(
		0.0f, (float)window_width,
		(float)window_height, 0.0f,
		0.0f, 1.0f
	);

	//ワールド行列の生成
	matWorld = XMMatrixTranslation(eye.x, eye.y, eye.z);

	//ビューポート行列の生成
	matViewPort = XMMatrixIdentity();
	matViewPort.r[0].m128_f32[0] = (float)window_width / 2.0f;
	matViewPort.r[1].m128_f32[1] = -1.0f * (float)(window_height / 2.0f);
	matViewPort.r[2].m128_f32[2] = 1.0f;
	matViewPort.r[3].m128_f32[0] = (float)window_width / 2.0f;
	matViewPort.r[3].m128_f32[1] = (float)window_height / 2.0f;
	matViewPort.r[3].m128_f32[3] = 1.0f;
}

void Camera2D::SetEye(XMFLOAT3 eye)
{
	Camera2D::eye = eye;

	UpdateViewMatrix();

	if (isMatWorldCalc) {
		UpdateWorldMatrix();
	}
}

void Camera2D::SetTarget(XMFLOAT3 target)
{
	Camera2D::target = target;

	UpdateViewMatrix();

	if (isMatWorldCalc) {
		UpdateWorldMatrix();
	}
}

void Camera2D::CameraMoveVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera2D::CameraMoveEyeVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera2D::CameraMoveTargetVector(XMFLOAT3 move) {
	XMFLOAT3  target_moved = GetTarget();

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetTarget(target_moved);
}

void Camera2D::UpdateViewMatrix() {

	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	XMVECTOR upVector = XMLoadFloat3(&up);

	XMVECTOR Camera2DAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	assert(!XMVector3Equal(Camera2DAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(Camera2DAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));

	Camera2DAxisZ = XMVector3Normalize(Camera2DAxisZ);
	XMVECTOR  Camera2DAxisX;
	Camera2DAxisX = XMVector3Cross(upVector, Camera2DAxisZ);
	Camera2DAxisX = XMVector3Normalize(Camera2DAxisX);

	XMVECTOR Camera2DAxisY;
	Camera2DAxisY = XMVector3Cross(Camera2DAxisZ, Camera2DAxisX);

	XMMATRIX matCamera2DRot;
	matCamera2DRot.r[0] = Camera2DAxisX;
	matCamera2DRot.r[1] = Camera2DAxisY;
	matCamera2DRot.r[2] = Camera2DAxisZ;
	matCamera2DRot.r[3] = XMVectorSet(0, 0, 0, 1);

	matBillboard.r[0] = Camera2DAxisX;
	matBillboard.r[1] = Camera2DAxisY;
	matBillboard.r[2] = Camera2DAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);

	XMVECTOR ybillCamera2DAxisX, ybillCamera2DAxisY, ybillCamera2DAxisZ;
	ybillCamera2DAxisX = Camera2DAxisX;
	ybillCamera2DAxisY = XMVector3Normalize(upVector);
	ybillCamera2DAxisZ = XMVector3Cross(ybillCamera2DAxisX, ybillCamera2DAxisY);

	matBillboardY.r[0] = ybillCamera2DAxisX;
	matBillboardY.r[1] = ybillCamera2DAxisY;
	matBillboardY.r[2] = ybillCamera2DAxisZ;
	matBillboardY.r[3] = XMVectorSet(0, 0, 0, 1);

	matView = XMMatrixTranspose(matCamera2DRot);

	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	XMVECTOR tX = XMVector3Dot(Camera2DAxisX, reverseEyePosition);
	XMVECTOR tY = XMVector3Dot(Camera2DAxisY, reverseEyePosition);
	XMVECTOR tZ = XMVector3Dot(Camera2DAxisZ, reverseEyePosition);

	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	matView.r[3] = translation;
}

void Camera2D::UpdateWorldMatrix()
{
	float xRot, yRot, zRot;
	XMFLOAT3 distance;
	XMMATRIX matRot, matTrans;

	distance = XMFLOAT3(eye.x - target.x, eye.y - target.y, eye.z - target.z);
	xRot = -(atan2(distance.y, sqrtf((float)pow(distance.z, 2)) + (float)pow(distance.x, 2)) * 180.0f / 3.14f);
	yRot = (atan2(distance.x, distance.z) * 180.0f / 3.14f);
	zRot = 0;
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(zRot));
	matRot *= XMMatrixRotationX(XMConvertToRadians(xRot));
	matRot *= XMMatrixRotationY(XMConvertToRadians(yRot));
	matTrans = XMMatrixTranslation(eye.x, eye.y, eye.z);

	up = XMFLOAT3{ matRot.r[1].m128_f32[0], matRot.r[1].m128_f32[1], matRot.r[1].m128_f32[2] };

	matWorld = XMMatrixIdentity();
	matWorld *= matRot;
	matWorld *= matTrans;

}

void Camera2D::SetUp(XMFLOAT3 up) {
	Camera2D::up = up;

	UpdateViewMatrix();
}

void Camera2D::SetMatWorld(XMMATRIX matWorld) {
	Camera2D::matWorld = matWorld;
	Camera2D::isMatWorldCalc = true;
}