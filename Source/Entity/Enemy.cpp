#include "Enemy.h"
#include "../Utility/ColorHelper.h"
#include "../Render/Avatar.h"

Enemy::Enemy(World* GameWorld)
	:
	Character(GameWorld)
{
	Initialize();
}

Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Initialize();
}

void Enemy::Initialize()
{
	Speed = 125.f;
	Avatar::SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW, CharacterRenderComponent.get());
}

void Enemy::Update(float DeltaTime)
{
	Character::Update(DeltaTime);

	ColorResetCounter++;
	if (ColorResetCounter >= ColorMaxTime)
	{
		SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW);
	}
}

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity * Speed;
}
