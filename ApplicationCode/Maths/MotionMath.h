#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

class MotionMath
{
private:
	MotionMath() = default;
	~MotionMath() = default;

public: //���w��p�񋓌^
	enum Axis {
		X,
		Y,
		Z
	};

public: //�����o�֐�
	/// <summary>
	/// �~�^��
	/// </summary>
	/// <param name="centerPos">���S���W</param>
	/// <param name="rotPos">��]��������W</param>
	/// <param name="angle">�p�x</param>
	/// <param name="length">���S���W�Ƃ̋���</param>
	/// <param name="axis">�ǂ̎��𒆐S�ɉ�]�����邩</param>
	/// <returns>���W</returns>
	static Vector3 CircularMotion(const Vector3& centerPos, const Vector3& rotPos, float angle, const float length, const Axis axis);

	/// <summary>
	/// �ꎟ���`���
	/// </summary>
	/// <param name="startPos">�J�n�n�_</param>
	/// <param name="endPos">�I���n�_</param>
	/// <param name="time">���Ԃ̊���</param>
	/// <returns>���W</returns>
	static Vector3 Leap(const Vector3& startPos, const Vector3& endPos, const float timeRate);
};

