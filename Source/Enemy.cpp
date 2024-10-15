#include "Enemy.h"
#include "ColorHelper.h"

Enemy::Enemy(const Vector2& InPosition)
	:
	Character(InPosition)
{
}

void Enemy::Initialize()
{
	SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW);
}
