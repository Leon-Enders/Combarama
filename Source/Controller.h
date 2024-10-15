#pragma once
#include <memory>
#include "Input/InputComponent.h"
#include "Input/InputAction.h"


//TODO: This class creates InputActions and an InputActionContext
struct Vector2;
class Game;
class Character;

class Controller
{
public:
	
	Controller();//Game* InOwningGame);

	virtual void PossessCharacter(Character* CharacterToPossess);

	

protected:
	virtual void Initialize();

	Character* ControlledCharacter = nullptr;
	Game* OwningGame = nullptr;
};