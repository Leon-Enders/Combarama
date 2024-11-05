#pragma once
#include <memory>
#include "Controller.h"
#include "../Entity/Enemy.h"


class AIController : public Controller
{
public:
	AIController(World* InOwningWorld);

	void Update(float DeltaTime);

	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess) override;

	virtual void UnPossessCharacter() override;

	void MoveEnemy();
	void RotateEnemy();
protected:

	virtual void Initialize() override;


private:

	void CheckForTarget();
	void HandleAttackFrequency();

private:


	Vector2 StartPosition = {};

	std::weak_ptr<Character> Target;
	std::weak_ptr<Enemy> ControlledEnemy;


	int VelocityUpdateCounter = 0;
	int VelocityMaxUpdateCounter = 120;

	float PullRange = 200.f;
	bool IsPulled = false;

	int AttackTimer = 0;
	int AttackResetTimer = 120;
};