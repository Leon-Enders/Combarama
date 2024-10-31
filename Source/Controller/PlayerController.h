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

	virtual void PossessCharacter(Character* CharacterToPossess) override;
	virtual void UnPossessCharacter() override;


protected:

	virtual void Initialize() override;
	
private:
	void Move(const InputActionValue& Value);
	void Look(const InputActionValue& Value);
	void Attack(const InputActionValue& Value);
	void Dash(const InputActionValue& Value);
	void Shoot(const InputActionValue& Value);

	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;

	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::shared_ptr<InputAction> MoveAction = nullptr;
	std::shared_ptr<InputAction> LookAction = nullptr;
	std::shared_ptr<InputAction> AttackAction = nullptr;
	std::shared_ptr<InputAction> DashAction = nullptr;
	std::shared_ptr<InputAction> ShootAction = nullptr;

	PlayerCharacter* ControlledPlayerCharacter = nullptr;
};