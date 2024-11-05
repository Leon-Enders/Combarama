#include "PlayerController.h"
#include "../Game.h"
#include "../Entity/PlayerCharacter.h"

PlayerController::PlayerController(World* InOwningWorld)
	:
	Controller(InOwningWorld)
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

	Initialize();
}

void PlayerController::Update(float DeltaTime)
{	
	HandleCooldowns();
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


	ControllerInputComponent->SetInputActionContext(ActionContext.get());
}

void PlayerController::PossessCharacter(Character* CharacterToPossess)
{
	ControlledPlayerCharacter = static_cast<PlayerCharacter*>(CharacterToPossess);
	ControlledPlayerCharacter->OnPossessed(this);
	ControlledPlayerCharacter->OnDeathSignature.AddMemberFunction<PlayerController>(this, &PlayerController::OnCharacterDeath);
	ControlledPlayerCharacter->OnDeathSignature.AddMemberFunction<PlayerController>(this, &PlayerController::OhNoCharacterdied);
}

void PlayerController::UnPossessCharacter()
{
	ControlledPlayerCharacter = nullptr;
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

void PlayerController::Dash(const InputActionValue& Value)
{
	if (!DashCooldownActive)
	{
		DashCooldownActive = true;
		ControlledPlayerCharacter->Dash();
	}
	
}

void PlayerController::Shoot(const InputActionValue& Value)
{
	if (!ShootCooldownActive)
	{
		ShootCooldownActive = true;
		ControlledPlayerCharacter->Shoot();
	}
}

void PlayerController::OnCharacterDeath()
{
	SDL_Log("Character Died!");
	//GetWorld()->RemoveController(this);
}

void PlayerController::OhNoCharacterdied()
{
	SDL_Log("Oh No Character died sadge");
}

void PlayerController::HandleCooldowns()
{
	if (DashCooldownActive)
	{
		DashCooldownCounter++;
		if (DashCooldownCounter > DashCooldownReset)
		{
			DashCooldownCounter = 0;
			DashCooldownActive = false;
		}
	}
	if (ShootCooldownActive)
	{
		ShootCooldownCounter++;
		if (ShootCooldownCounter > ShootCooldownReset)
		{
			ShootCooldownCounter = 0;
			ShootCooldownActive = false;
		}
	}
}
