#pragma once
#include <memory>
#include "Input/InputComponent.h"
#include "Input/InputAction.h"


//TODO: This class creates InputActions and an InputActionContext
struct Vector2;
class Game;
class Actor;

class Controller
{
public:
	
	Controller(Game* InOwningGame);

	void PossessActor(Actor* ActorToPossess);

private:

	void Move(const Vector2& InVelocity);

	void Initialize();

private:
	Game* OwningGame = nullptr;
	Actor* ControlledActor = nullptr;


	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;

	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::shared_ptr<InputAction> MoveAction = nullptr;
};