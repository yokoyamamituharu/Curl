#include "BaseEnemy.h"
#include "SafeDelete.h"
#include"Collision.h"

std::vector<Sprite*> BaseEnemy::SpritesCreate(const ImageManager::ImageName imageName, const int32_t animationCount, const Vector2& enemyPos)
{
	std::vector<Sprite*> sprites;

	for (int32_t i = 0; i < animationCount; i++) {
		sprites.push_back(Sprite::Create((UINT)imageName, enemyPos));
		sprites[i]->SetAnchorPoint({ 0.5f, 0.5f });
		sprites[i]->SetPosition(enemyPos);
		Vector2 texBase = { 0.0f, 0.0f };
		texBase.x = 64.0f * (float)i;
		sprites[i]->SetSize({ 64.0f, 64.0f });
		sprites[i]->SetTextureRect(texBase, { 64.0f, 64.0f });
	}
	return sprites;
}

void BaseEnemy::WorldMarker(XMFLOAT2 playerPos)
{
	
	if (pos.x <= -32.f || pos.x >= (float)WinApp::window_width + 32.f)
	{
		widthFlag = true;
	}

	if (pos.y <= -32.f || pos.y >= (float)WinApp::window_height + 32.f)
	{
		heightFlag = true;
	}

	if (widthFlag == true || heightFlag == true)
	{

		//atan2(pos.x - ((float)WinApp::window_width / 2), pos.y - ((float)WinApp::window_height / 2));
		atan2(pos.x - playerPos.x, pos.y - playerPos.y);

	}
}