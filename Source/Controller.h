#pragma once
#include <memory>
#include "Input/InputComponent.h"
#include "Input/InputAction.h"

//TODO: This class creates InputActions and an InputActionContext
class Game;
class Controller
{
public:
	
	Controller(Game* InOwningGame);
	void Initialize();

private:

	Game* OwningGame = nullptr;
	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;
};