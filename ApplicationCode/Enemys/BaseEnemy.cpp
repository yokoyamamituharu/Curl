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

void BaseEnemy::WorldMarker(XMFLOAT2 camera)
{

#pragma region 描画がスクリーンの外で行われているかの判定

	//スクリーンの最小値　- 32
	//スクリーンの最大値　+ 32
	//上の二つの中にプレイヤーがいるかの判定

#pragma endregion 描画がスクリーンの外で行われているかの判定

#pragma region マーカーを出すための処理

	//上の判定で外にいた場合

	//ホーミング弾と似た処理
	
	XMVECTOR vec;

	vec.m128_f32[0] = (camera.x - pos.x);
	vec.m128_f32[1] = (camera.y - pos.y);
	vec = DirectX::XMVector2Normalize(vec);

	markerAdd.m128_f32[0] = vec.m128_f32[0] * markerLength;
	markerAdd.m128_f32[1] = vec.m128_f32[1] * markerLength;

	markerPos.x = pos.x + markerAdd.m128_f32[0];
	markerPos.y = pos.y + markerAdd.m128_f32[1];

#ifdef フラグ処理

	if (pos.x < /*スクリーンの最小値 - 32*/)
	{
		if (markerPos.x >/*スクリーンの最小値 - 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//フラグの終了
		}
	}
	else if (pos.x > /*スクリーンの最大値 + 32*/)
	{
		if (markerPos.x </*スクリーンの最小値 + 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//フラグの終了
		}
	}
	else
	{

	}

	if (pos.y < /*スクリーンの最小値 - 32*/)
	{
		if (markerPos.y >/*スクリーンの最小値 - 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//フラグの終了
		}
	}
	else if (pos.y > /*スクリーンの最大値 + 32*/)
	{
		if (markerPos.y </*スクリーンの最小値 + 32*/)
		{
			markerAngle = atan2f(pos.x - camera.x, pos.y - camera.y);

			//フラグの終了
		}
	}
	else
	{

	}
#endif // フラグ処理

	


#pragma endregion マーカーを出すための処理


	//atan2(pos.x - ((float)WinApp::window_width / 2), pos.y - ((float)WinApp::window_height / 2));
	


}