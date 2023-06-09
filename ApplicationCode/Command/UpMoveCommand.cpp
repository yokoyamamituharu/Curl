#include "UpMoveCommand.h"
#include "Vector2.h"

void UpMoveCommand::Execute(Player* player)
{
	//上方向への移動ベクトル
	const Vector2 moveVec = { 0.0f, -1.0f*player->GetSpeed()};
	player->AddPlayerVector(moveVec);
}
