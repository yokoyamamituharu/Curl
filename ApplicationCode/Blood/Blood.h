#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
class Blood
{
public:
	enum STATE {
		NONE,
		solid,
		liquid,
		gas
	};

	Blood() = default;

	~Blood();

	static Blood* Create(DirectX::XMFLOAT2 position, STATE state);

	static std::unique_ptr<Blood> UniquePtrCreate(DirectX::XMFLOAT2 position, STATE state, DirectX::XMFLOAT2 goal);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// ���x���㏸������
	/// </summary>
	void Rising();
	/// <summary>
	/// ���x������������
	/// </summary>
	void Decrease();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// ���S������擾
	/// </summary>
	/// <returns>���S����</returns>
	bool GetDead();
	/// <summary>
	/// ���S����ɂ���
	/// </summary>
	void SetDead();
	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	int GetTemperature() { return state_; }
	/// <summary>
	/// �ʒu���擾
	/// </summary>
	/// <returns>�ʒu</returns>
	DirectX::XMFLOAT2 GetPosition() { return position_; }

private:

public:

private:
	std::map<int, Sprite*> sprites_;
	int state_ = NONE;
	int deadTimer = 100;
	bool isDead = false;
	DirectX::XMFLOAT2 position_{};
	DirectX::XMFLOAT2 goal_{};
	DirectX::XMVECTOR oldvec{};

	const float speed_ = 10.0f;
};