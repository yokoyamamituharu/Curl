#pragma once
#include "Player.h"
#include "PlayerCommand.h"

class LeftMoveCommand : public PlayerCommand
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LeftMoveCommand() = default;

public:
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="player"></param>
	void Execute(Player* player);
};

