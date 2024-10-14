#include "Controller.h"
#include "Game.h"
#include "Actor.h"
#include "Vector2.h"


Controller::Controller(Game* InOwningGame)
	:
	OwningGame(InOwningGame)
{
	using namespace std::placeholders;
	ActionContext = std::make_unique<InputActionContext>();
	ControllerInputComponent = std::make_unique<InputComponent>();

	QuitAction = std::make_shared<InputAction>(ActionValueType::None);
	QuitAction->BindFunction(std::bind(&Game::QuitGame, OwningGame));

	MoveAction = std::make_shared<InputAction>(ActionValueType::Vector);
	MoveAction->BindFunction<Vector2>(std::bind(&Controller::Move, this, _1));


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
	ActionContext->AddInputAction(SDLK_Q, MoveAction);


	ControllerInputComponent->SetInputActionContext(ActionContext.get());

}
