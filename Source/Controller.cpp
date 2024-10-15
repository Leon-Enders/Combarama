#include "Controller.h"
#include "Game.h"
#include "Actor.h"
#include "Vector2.h"
#include <cmath>


Controller::Controller(Game* InOwningGame)
	:
	OwningGame(InOwningGame)
{
	using namespace std::placeholders;
	ActionContext = std::make_unique<InputActionContext>();
	ControllerInputComponent = std::make_unique<InputComponent>();

	QuitAction = std::make_shared<InputAction>();
	QuitAction->BindFunction(std::bind(&Game::QuitGame, OwningGame));

	MoveAction = std::make_shared<InputAction>();
	MoveAction->BindFunction(std::bind(&Controller::Move, this, _1));

	LookAction = std::make_shared<InputAction>();
	LookAction->BindFunction(std::bind(&Controller::Look, this, _1));

	Initialize();
}

void Controller::PossessActor(Actor* ActorToPossess)
{
	ControlledActor = ActorToPossess;
}

void Controller::Move(const InputActionValue& Value)
{
	
	ControlledActor->UpdateVelocity(Value.Get<Vector2>());
}

void Controller::Look(const InputActionValue& Value)
{
	Vector2 TargetMousePosition = Value.Get<Vector2>();
	ControlledActor->ReceiveMouseInput(TargetMousePosition);
}

void Controller::Initialize()
{
	KeycodePackage MoveKeyPackage;
	MoveKeyPackage.AddKeycode(SDLK_W, E_AxisMapping::Up);
	MoveKeyPackage.AddKeycode(SDLK_S, E_AxisMapping::Down);
	MoveKeyPackage.AddKeycode(SDLK_A, E_AxisMapping::Left);
	MoveKeyPackage.AddKeycode(SDLK_D, E_AxisMapping::Right);
	//ActionContext->AddInputAction(SDLK_ESCAPE, QuitAction);

	ActionContext->AddInputActionBinding(MoveKeyPackage, MoveAction);
	ActionContext->AddLookInputAction(LookAction);
	ActionContext->AddQuitInputAction(QuitAction);


	ControllerInputComponent->SetInputActionContext(ActionContext.get());

}
