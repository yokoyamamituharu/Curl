#include "Vector3.h"

using namespace DirectX;

//�R���X�g���N�^
Vector3::Vector3() : Vector3(0, 0, 0)
{

}

Vector3::Vector3(float x, float y, float z) : XMFLOAT3{ x, y, z }
{

}

Vector3::Vector3(const XMFLOAT3& vec) : XMFLOAT3{ x, y, z } {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Vector3::Vector3(const XMVECTOR& vec) : XMFLOAT3{ x, y, z } {
	XMStoreFloat3(this, vec);
}

//���������߂�
float Vector3::length() const
{
	return (float)sqrtf(x * x + y * y + z * z);
}

//���K��
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

//���ς����߂�
float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

//�O�ς����߂�
Vector3 Vector3::cross(const Vector3& v) const
{
	Vector3 temp;
	temp.x = this->y * v.z - this->z * v.y;
	temp.y = this->z * v.x - this->x * v.z;
	temp.z = this->x * v.y - this->y * v.x;
	return temp;
}

//�P�����Z�q�I�[�o�[���[�h
Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

//������Z�q�I�[�o�[���[�h
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

//2�����Z�q�I�[�o�[���[�h
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

//���`���
const Vector3 lerp(const Vector3 &start, const Vector3 &end, const float t) 
{
	return start * (1.0f - t) + end * t;
}

const Vector3 easeIn(const Vector3& start, const Vector3& end, const float t)
{
	float y = t * t;
	return start * (1.0f - y) + end * y;
}

const Vector3 easeOut(const Vector3& start, const Vector3& end, const float t)
{
	float y = t * (2 - t);
	return start * (1.0f - y) + end * y;
}
