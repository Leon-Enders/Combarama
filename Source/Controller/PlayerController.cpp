#include "PlayerController.h"
#include "../Game.h"
#include "../Entity/PlayerCharacter.h"

PlayerController::PlayerController()//Game* InOwningGame)
{
	using namespace std::placeholders;
	ActionContext = std::make_unique<InputActionContext>();
	ControllerInputComponent = std::make_unique<InputComponent>();

	//QuitAction = std::make_shared<InputAction>();
	//QuitAction->BindFunction(std::bind(&Game::QuitGame, OwningGame));

	MoveAction = std::make_shared<InputAction>();
	MoveAction->BindFunction(std::bind(&PlayerController::Move, this, _1));

	LookAction = std::make_shared<InputAction>();
	LookAction->BindFunction(std::bind(&PlayerController::Look, this, _1));

	AttackAction = std::make_shared<InputAction>();
	AttackAction->BindFunction(std::bind(&PlayerController::Attack, this, _1));


	Initialize();
}

void PlayerController::Initialize()
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
	ActionContext->AddAttackInputAction(AttackAction);

	ControllerInputComponent->SetInputActionContext(ActionContext.get());
}

void PlayerController::PossessCharacter(Character* CharacterToPossess)
{
	ControlledPlayerCharacter = static_cast<PlayerCharacter*>(CharacterToPossess);
	ControlledPlayerCharacter->OnPossessed(this);
}

void PlayerController::Move(const InputActionValue& Value)
{
	ControlledPlayerCharacter->UpdateVelocity(Value.Get<Vector2>());
}

void PlayerController::Look(const InputActionValue& Value)
{
	Vector2 TargetMousePosition = Value.Get<Vector2>();
	ControlledPlayerCharacter->ReceiveMouseInput(TargetMousePosition);
}

void PlayerController::Attack(const InputActionValue& Value)
{
	ControlledPlayerCharacter->Attack();
}
