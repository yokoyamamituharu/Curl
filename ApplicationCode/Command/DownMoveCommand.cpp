#include "DownMoveCommand.h"
#include "Vector2.h"

void DownMoveCommand::Execute(Player* player)
{
	//下方向への移動ベクトル
	const Vector2 moveVec = { 0.0f, +1.0f * player->GetSpeed() };
	player->AddPlayerVector(moveVec);
}