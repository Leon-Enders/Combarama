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

	float MaxXDistance = 200.f;

};