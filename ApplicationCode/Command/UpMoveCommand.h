#pragma once
#include "Player.h"
#include "PlayerCommand.h"

class UpMoveCommand : public PlayerCommand
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UpMoveCommand() = default;

public:
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="player"></param>
	void Execute(Player* player);
};

