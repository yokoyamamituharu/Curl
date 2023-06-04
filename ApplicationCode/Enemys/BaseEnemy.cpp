#include "BaseEnemy.h"
#include "SafeDelete.h"

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
