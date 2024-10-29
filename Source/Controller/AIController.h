#pragma once
#include <memory>
#include "Controller.h"
#include "../Entity/Enemy.h"


class AIController : public Controller
{
public:
	AIController(World* InOwningWorld);
	void SetTarget(Character* TargetCharacter);
	virtual void PossessCharacter(Character* CharacterToPossess) override;

	virtual void UnPossessCharacter() override;

	void MoveEnemy();
protected:

	virtual void Initialize() override;

private:


	Vector2 StartPosition = {};

	Character* Target = nullptr;
	Enemy* ControlledEnemy = nullptr;


	int VelocityUpdateCounter = 0;
	int VelocityMaxUpdateCounter = 120;
};