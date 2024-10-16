#include "Controller.h"
#include "../Game.h"
#include "../Entity/Character.h"


Controller::Controller()//Game* InOwningGame)
{
	Initialize();
}

void Controller::PossessCharacter(Character* CharacterToPossess)
{
	ControlledCharacter = CharacterToPossess;
	ControlledCharacter->OnPossessed(this);
}


void Controller::Initialize()
{
	
}
