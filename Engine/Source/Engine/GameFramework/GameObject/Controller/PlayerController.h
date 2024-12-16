#pragma once
#include "Controller.h"
#include <memory>
#include "../../../Input/InputComponent.h"
#include "../../../Input/InputAction.h"
#include "../../../../Core/Coroutine/Coroutine.h"
#include "../../../../Core/Coroutine/WaitSeconds.h"

class PlayerCharacter;

class PlayerController : public Controller, public std::enable_shared_from_this<PlayerController>
{
public:
	PlayerController(World* OwningWorld);
	~PlayerController() = default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;



	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess) override;
	virtual void UnPossessCharacter() override;

	//TODO: When implementing cooldowns for "abilities" we need the all controllers to have an update method and be updated by the world or rather by a subsystem?
	//Should AISystem Updating AIControllers be a thing?
private:
	// Action Callbacks
	void Move(const InputActionValue& Value);
	void Look(const InputActionValue& Value);
	void Attack(const InputActionValue& Value);
	void Dash(const InputActionValue& Value);
	void Shoot(const InputActionValue& Value);
	void Zoom(const InputActionValue& Value);

	void OnCharacterDestroyed();


	std::unique_ptr<InputComponent> ControllerInputComponent;
	std::unique_ptr<InputActionContext> ActionContext;

	std::shared_ptr<InputAction> QuitAction;
	std::shared_ptr<InputAction> MoveAction;
	std::shared_ptr<InputAction> LookAction;
	std::shared_ptr<InputAction> AttackAction;
	std::shared_ptr<InputAction> DashAction;
	std::shared_ptr<InputAction> ShootAction;
	std::shared_ptr<InputAction> ScrollAction;

	std::weak_ptr<PlayerCharacter> ControlledPlayerCharacter;


	//Cooldowns
	bool DashReady = true;
	float DashCooldownTime = 1.f;

	bool ShootReady = true;
	float ShootCooldownTime = 0.3f;
};