#include "Controller.h"
#include "../Game.h"
#include "../Entity/Character.h"


Controller::Controller(World* InOwningWorld)
	:
	OwningWorld(InOwningWorld)
{
	Initialize();
}

void Controller::Update(float DeltaTime)
{

}

void Controller::PossessCharacter(Character* CharacterToPossess)
{
	ControlledCharacter = CharacterToPossess;
	ControlledCharacter->OnPossessed(this);
	ControlledCharacter->OnDestroyDelegate = std::bind(&Controller::UnPossessCharacter,this);
}

void Controller::UnPossessCharacter()
{
	ControlledCharacter = nullptr;
}


void Controller::Initialize()
{
	
}
