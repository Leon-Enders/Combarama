#include "Character.h"

Character::Character()
{
}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}
