#pragma once
#include "Sprite.h"
#include <vector>
#include <map>
#include "Vector2.h"

class Blood
{
public:
	enum class Temperature
	{
		NONE,
		solid,
		liquid,
		gas,
		droppedLiquid
	};

	enum class State {
		none,
		idle,
		shot,
		back,
		heat
	};

	Blood() = default;

	~Blood();

	static Blood* Create(DirectX::XMFLOAT2 position, Temperature state);

	static std::unique_ptr<Blood> UniquePtrCreate(Vector2 position, Temperature state, Vector2 targetPos_, Vector2* playerPos);

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
	int GetTemperature() { return temp_; }
	/// <summary>
	/// �ʒu���擾
	/// </summary>
	/// <returns>�ʒu</returns>
	DirectX::XMFLOAT2 GetPosition() { return position_; }
	/// <summary>
	/// 
	/// </summary>
	void SetState(State state) { state_ = (int)state; }

	int GetState() { return state_; }

	Vector2  GetPos() { return position_; }

	void HeatWaveOnCollision();
	void ColdWaveOnCollision();
private:

public:

private:
	std::map<int, Sprite*> sprites_;
	int temp_ = (int)Temperature::NONE;
	int state_ = (int)State::none;
	int deadTimer_ = 100;
	bool isDead = false;
	Vector2 position_{};
	Vector2 targetPos_{};
	Vector2 oldvec_{};
	Vector2* playerPos_{};
	const float speed_ = 5.0f;
	int maxTempDray = 20;
	int tempDray = 0;
};