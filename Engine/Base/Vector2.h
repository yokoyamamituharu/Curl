#pragma once
#include <DirectXMath.h>

class Vector2 : public DirectX::XMFLOAT2
{
public:
	//�R���X�g���N�^
	Vector2();
	Vector2(float x, float y);
	Vector2(const DirectX::XMFLOAT2& vec);
	Vector2(const DirectX::XMVECTOR& vec);

	//�����o�֐�
	float length() const;
	Vector2& normalize();
	float dot(const Vector2& v) const;

	//�P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(const Vector2& v);
	Vector2& operator/=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

//2�����Z�q�I�[�o�[���[�h
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

//��Ԋ֐�
//���`���(1���֐����)
const Vector2 lerp(const Vector2& start, const Vector2& end, const float t);

//���`���(�C�[�Y�C��)
const Vector2 easeIn(const Vector2& start, const Vector2& end, const float t);

//���`���(�C�[�Y�A�E�g)
const Vector2 easeOut(const Vector2& start, const Vector2& end, const float t);