#include "LeftMoveCommand.h"
#include "Vector2.h"

void LeftMoveCommand::Execute(Player* player)
{
	//左方向への移動ベクトル
	const Vector2 moveVec = { -1.0f * player->GetSpeed(), 0.0f};
	player->AddPlayerVector(moveVec);
}
