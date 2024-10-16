#pragma once

#include "Controller.h"

class Enemy;

class AIController : public Controller
{
public:
	AIController();

	virtual void PossessCharacter(Character* CharacterToPossess) override;
protected:

	virtual void Initialize() override;

private:
	
	Enemy* ControlledEnemy = nullptr;
};