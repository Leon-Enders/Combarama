#pragma once
#include "Controller.h"
#include <memory>
#include "../Input/InputComponent.h"
#include "../Input/InputAction.h"

class PlayerCharacter;

class PlayerController : public Controller
{
public:
	PlayerController(World* InOwningWorld);

	virtual void Update(float DeltaTime) override;

	virtual void PossessCharacter(Character* CharacterToPossess) override;
	virtual void UnPossessCharacter() override;

	//TODO: When implementing cooldowns for "abilities" we need the all controllers to have an update method and be updated by the world or rather by a subsystem?
	//Should AISystem Updating AIControllers be a thing?
protected:

	virtual void Initialize() override;
	
private:


	// Action Callbacks
	void Move(const InputActionValue& Value);
	void Look(const InputActionValue& Value);
	void Attack(const InputActionValue& Value);
	void Dash(const InputActionValue& Value);
	void Shoot(const InputActionValue& Value);

	// Cooldowns
	void HandleCooldowns();

	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;

	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::shared_ptr<InputAction> MoveAction = nullptr;
	std::shared_ptr<InputAction> LookAction = nullptr;
	std::shared_ptr<InputAction> AttackAction = nullptr;
	std::shared_ptr<InputAction> DashAction = nullptr;
	std::shared_ptr<InputAction> ShootAction = nullptr;

	PlayerCharacter* ControlledPlayerCharacter = nullptr;



	//Cooldowns
	bool DashCooldownActive = false;
	int DashCooldownCounter = 0;
	int DashCooldownReset = 120;

	bool ShootCooldownActive = false;
	int ShootCooldownCounter = 0;
	int ShootCooldownReset = 30;
};