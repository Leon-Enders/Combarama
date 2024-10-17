#pragma once
#include "Controller.h"

class PlayerCharacter;

class PlayerController : public Controller
{
public:
	PlayerController();

	virtual void PossessCharacter(Character* CharacterToPossess) override;
protected:

	virtual void Initialize() override;
	
private:
	void Move(const InputActionValue& Value);
	void Look(const InputActionValue& Value);
	void Attack(const InputActionValue& Value);

	std::unique_ptr<InputComponent> ControllerInputComponent = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;

	std::shared_ptr<InputAction> QuitAction = nullptr;
	std::shared_ptr<InputAction> MoveAction = nullptr;
	std::shared_ptr<InputAction> LookAction = nullptr;
	std::shared_ptr<InputAction> AttackAction = nullptr;

	PlayerCharacter* ControlledPlayerCharacter = nullptr;
};