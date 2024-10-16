#include "AIController.h"
#include "../Entity/Enemy.h"

AIController::AIController()
{

}

void AIController::PossessCharacter(Character* CharacterToPossess)
{
	ControlledEnemy = static_cast<Enemy*>(CharacterToPossess);
	ControlledEnemy->OnPossessed(this);
}

void AIController::Initialize()
{

}
