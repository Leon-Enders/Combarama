#pragma once
#include <memory>
#include "Controller.h"
#include "../Entity/Enemy.h"


class AIController : public Controller
{
public:
	AIController();

	virtual void PossessCharacter(Character* CharacterToPossess) override;
protected:

	virtual void Initialize() override;

private:
	
	std::unique_ptr<Enemy> ControlledEnemy = nullptr;
};