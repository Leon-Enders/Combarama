#include "Character.h"

Character::Character(const Vector2& InPosition)
	:
	Actor(InPosition)
{
	Position = InPosition;
}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}

void Character::UpdatePosition(float DeltaTime)
{
	Actor::UpdatePosition(DeltaTime);
}

void Character::Initialize()
{
}
