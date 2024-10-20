#include "Enemy.h"
#include "../Utility/ColorHelper.h"
#include "../Render/Avatar.h"

Enemy::Enemy(const Transform& InTransform)
	:
	Character(InTransform)
{
	Speed = 0.2f;
}

void Enemy::Initialize()
{
	Avatar::SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW, CharacterRenderComponent.get());
}

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}
