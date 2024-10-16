#include "Enemy.h"
#include "../Utility/ColorHelper.h"

Enemy::Enemy(const Vector2& InPosition)
	:
	Character(InPosition)
{
	Speed = 0.2f;
}

void Enemy::Initialize()
{
	SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW);
}

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}
