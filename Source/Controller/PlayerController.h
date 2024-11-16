#pragma once
#include "Controller.h"
#include <memory>
#include "../Input/InputComponent.h"
#include "../Input/InputAction.h"
#include "../Coroutine/Coroutine.h"
#include "../Coroutine/Awaitable/WaitSeconds.h"

class PlayerCharacter;

class PlayerController : public Controller, public std::enable_shared_from_this<PlayerController>
{
public:
	PlayerController(World* InOwningWorld);

	virtual void Update(float DeltaTime) override;

	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess) override;
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


	void OnCharacterDestroyed();


	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;

	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::shared_ptr<InputAction> MoveAction = nullptr;
	std::shared_ptr<InputAction> LookAction = nullptr;
	std::shared_ptr<InputAction> AttackAction = nullptr;
	std::shared_ptr<InputAction> DashAction = nullptr;
	std::shared_ptr<InputAction> ShootAction = nullptr;

	std::weak_ptr<PlayerCharacter> ControlledPlayerCharacter;



	//Cooldowns
	bool DashReady = true;
	float DashCooldownTime = 1.f;

	bool ShootReady = true;
	float ShootCooldownTime = 0.3f;


	
private:
	//Coroutines

	Coroutine ActivateDashCooldown()
	{
		DashReady = false;
		co_await WaitSeconds(DashCooldownTime);
		DashReady = true;
	}


	Coroutine ActivateShootCooldown()
	{
		ShootReady = false;
		co_await WaitSeconds(ShootCooldownTime);
		ShootReady = true;
	}

};