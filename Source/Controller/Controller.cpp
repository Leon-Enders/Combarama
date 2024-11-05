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


void Controller::PossessCharacter(std::shared_ptr<Character> CharacterToPossess)
{
	ControlledCharacter = CharacterToPossess;
	if (auto SharedCharacterPtr = ControlledCharacter.lock())
	{
		SharedCharacterPtr->OnPossessed(this);
		SharedCharacterPtr->OnDestroyDelegate = std::bind(&Controller::UnPossessCharacter, this);
	}
}

void Controller::UnPossessCharacter()
{
	ControlledCharacter.reset();
}


void Controller::Initialize()
{
	
}
