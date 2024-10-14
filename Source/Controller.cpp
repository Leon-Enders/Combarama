#include "Controller.h"
#include "Game.h"
#include "Actor.h"
#include "Vector2.h"


Controller::Controller(Game* InOwningGame)
	:
	OwningGame(InOwningGame)
{
	ActionContext = std::make_unique<InputActionContext>();
	ControllerInputComponent = std::make_unique<InputComponent>();

	QuitAction = std::make_shared<InputAction>(std::bind(&Game::QuitGame, OwningGame));
	MoveAction = std::make_shared<InputAction>(std::bind(&Controller::Move, this));



	Initialize();
}

void Controller::PossessActor(Actor* ActorToPossess)
{
	ControlledActor = ActorToPossess;
}

void Controller::Move(const Vector2& InVelocity)
{
	ControlledActor->UpdateVelocity(InVelocity);
}

void Controller::Initialize()
{
	ActionContext->AddInputAction(SDLK_ESCAPE, QuitAction);

	ControllerInputComponent->SetInputActionContext(ActionContext.get());

}
