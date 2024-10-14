#include "Controller.h"
#include "Game.h"


Controller::Controller(Game* InOwningGame)
	:
	OwningGame(InOwningGame)
{

	QuitAction = std::make_shared<InputAction>(std::bind(&Game::QuitGame, OwningGame));
	ActionContext = std::make_unique<InputActionContext>();
	ControllerInputComponent = std::make_unique<InputComponent>();

	Initialize();
}

void Controller::Initialize()
{
	ActionContext->AddInputAction(SDLK_ESCAPE, QuitAction);

	ControllerInputComponent->SetInputActionContext(ActionContext.get());
}
