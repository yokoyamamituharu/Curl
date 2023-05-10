#include "Player.h"
#include "SafeDelete.h"
#include "KeyInput.h"
#include "ImageManager.h"
#include "MouseInput.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(sprite_);
}

Player* Player::Create()
{
	Player* instance = new Player();
	instance->sprite_ = Sprite::Create(UINT(ImageManager::ImageName::playerTexNumber), { 0,0 });
	instance->sprite_->SetSize({ 128, 128 });
	return instance;
}

void Player::Update()
{
	float speed = 2.0f;
	DirectX::XMVECTOR vec = {};
	if (KeyInput::GetIns()->PushKey(DIK_D))	vec.m128_f32[0] += speed;
	if (KeyInput::GetIns()->PushKey(DIK_A))	vec.m128_f32[0] -= speed;
	if (KeyInput::GetIns()->PushKey(DIK_W))	vec.m128_f32[1] -= speed;
	if (KeyInput::GetIns()->PushKey(DIK_S))	vec.m128_f32[1] += speed;

	sprite_->SetPosition({ sprite_->GetPosition().x + vec.m128_f32[0],sprite_->GetPosition().y + vec.m128_f32[1] });

	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Update();
	}

	bloods_.remove_if([](std::unique_ptr<Blood>& blood) {
		return blood->GetDead();
		});

	Shot();

	XMFLOAT2 cursolPos = DirectX::XMFLOAT2{ float(MouseInput::GetIns()->GetMousePoint().x),float(MouseInput::GetIns()->GetMousePoint().y)};
	XMFLOAT2 playerPos = sprite_->GetPosition();
	DirectX::XMVECTOR vec3 = { cursolPos.x - playerPos.x,cursolPos.y - playerPos.y };
	vec3 = DirectX::XMVector3Normalize(vec3);
	XMFLOAT2 vec2 = { vec3.m128_f32[0],vec3.m128_f32[1] };

	if (KeyInput::GetIns()->PushKey(DIK_SPACE)) {
		bloods_.push_back(Blood::UniquePtrCreate({ sprite_->GetPosition() }, Blood::solid, vec2));
	}
}

void Player::Shot()
{
	//if (KeyInput::GetIns()->PushKey(DIK_SPACE)) {
	//	bloods_.push_back(Blood::UniquePtrCreate({ sprite_->GetPosition() }, Blood::solid,vec));
	//}
}

void Player::Draw()
{
	sprite_->Draw();
	for (std::unique_ptr<Blood>& blood : bloods_) {
		blood->Draw();
	}
}