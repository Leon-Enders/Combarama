#include "PlayerController.h"
#include "../../Core/CoreMinimal.h"
#include "../Character/PlayerCharacter.h"
#include "../../Math/ComboramaMath.h"
#include "../../Component/CameraComponent.h"


PlayerController::PlayerController(World* OwningWorld)
	:
	Controller(OwningWorld)
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

	DashAction = std::make_shared<InputAction>();
	DashAction->BindFunction(std::bind(&PlayerController::Dash, this, _1));

	ShootAction = std::make_shared<InputAction>();
	ShootAction->BindFunction(std::bind(&PlayerController::Shoot, this, _1));

	ScrollAction = std::make_shared<InputAction>();
	ScrollAction->BindFunction(std::bind(&PlayerController::Zoom, this, _1));
}

void PlayerController::Update(float DeltaTime)
{	
}

void PlayerController::Initialize()
{
	KeycodePackage MoveKeyPackage;
	MoveKeyPackage.AddKeycode(SDLK_W, E_AxisMapping::Up);
	MoveKeyPackage.AddKeycode(SDLK_S, E_AxisMapping::Down);
	MoveKeyPackage.AddKeycode(SDLK_A, E_AxisMapping::Left);
	MoveKeyPackage.AddKeycode(SDLK_D, E_AxisMapping::Right);
	//ActionContext->AddInputAction(SDLK_ESCAPE, QuitAction);


	// Can Bind Multiple keys for the same action here
	KeycodePackage DashKeyPackage;
	DashKeyPackage.AddKeycode(SDLK_BACKSPACE, E_AxisMapping::Up);
	DashKeyPackage.AddKeycode(SDLK_SPACE, E_AxisMapping::Down);
	

	ActionContext->AddInputActionBinding(DashKeyPackage, DashAction);
	

	ActionContext->AddInputActionBinding(MoveKeyPackage, MoveAction);
	ActionContext->AddLookInputAction(LookAction);
	ActionContext->AddQuitInputAction(QuitAction);
	ActionContext->AddAttackInputAction(AttackAction);
	ActionContext->AddShootInputAction(ShootAction);
	ActionContext->AddScrollInputAction(ScrollAction);


	ControllerInputComponent->SetInputActionContext(ActionContext.get());
}

void PlayerController::PossessCharacter(std::shared_ptr<Character> CharacterToPossess)
{

	ControlledPlayerCharacter = std::dynamic_pointer_cast<PlayerCharacter>(CharacterToPossess);
	if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
	{
		sPlayerPtr->SetController(shared_from_this());
		sPlayerPtr->OnDestroyDelegate.AddMemberFunction<PlayerController>(shared_from_this(), &PlayerController::OnCharacterDestroyed);
	}
}

void PlayerController::UnPossessCharacter()
{
	ControlledPlayerCharacter.reset();
}

void PlayerController::Move(const InputActionValue& Value)
{
	if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
	{
		sPlayerPtr->UpdateVelocity(Value.Get<Vector2>());
	}
}

void PlayerController::Look(const InputActionValue& Value)
{
	Vector2 TargetMousePosition = Value.Get<Vector2>();
	if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
	{
		Vector2 DeltaPosition = TargetMousePosition - sPlayerPtr->GetPosition();
		ControlRotation = std::atan2f(DeltaPosition.Y, DeltaPosition.X);
	}
}

void PlayerController::Attack(const InputActionValue& Value)
{
	if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
	{
		sPlayerPtr->Attack();
	}
	
}

void PlayerController::Dash(const InputActionValue& Value)
{
	if (DashReady)
	{

		if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
		{
			sPlayerPtr->Dash();
		}
	}
}

void PlayerController::Shoot(const InputActionValue& Value)
{
	if (ShootReady)
	{
	
		if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
		{
			sPlayerPtr->Shoot();
		}
	}
}

void PlayerController::Zoom(const InputActionValue& Value)
{
	
	//if (auto sPlayerPtr = ControlledPlayerCharacter.lock())
	//{
	//	CameraComponent* Camera = sPlayerPtr->GetCamera();
	//	float Scale = Value.Get<float>();
	//
	//	Vector2 ScaleVec(Scale, Scale);
	//
	//	Camera->SetScale(Camera->GetTransform().Scale + ScaleVec);
	//}

	
}

void PlayerController::OnCharacterDestroyed()
{
	SDL_Log("Character died");
	UnPossessCharacter();
}
