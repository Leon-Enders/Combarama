#include "Controller.h"
#include "../Game.h"
#include "../Entity/Character.h"


Controller::Controller(World* OwningWorld)
	:
	GameObject(OwningWorld)
{
	Initialize();
}

void Controller::Update(float DeltaTime)
{

}


void Controller::PossessCharacter(std::shared_ptr<Character> CharacterToPossess)
{
	
}

void Controller::UnPossessCharacter()
{
	
}


void Controller::Initialize()
{
	
}
