#pragma once
#include "Player.h"

class PlayerCommand {
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerCommand() {}

public: //�����o�֐�
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="player"></param>
	virtual void Execute(Player* player) = 0;
};