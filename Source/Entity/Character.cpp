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

void Character::Initialize()
{
}
