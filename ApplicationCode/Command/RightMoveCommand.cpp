#include "RightMoveCommand.h"
#include "Vector2.h"

void RightMoveCommand::Execute(Player* player)
{
	//�E�����ւ̈ړ��x�N�g��
	const Vector2 moveVec = { 1.0f * player->GetSpeed(), 0.0f};
	player->AddPlayerVector(moveVec);
}
