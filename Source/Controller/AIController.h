#pragma once
#include <memory>
#include "Controller.h"
#include "../Math/Vector2.h"
#include "../Coroutine/Coroutine.h"
	


class Enemy;

class AIController : public Controller, public std::enable_shared_from_this<AIController>
{
public:
	AIController(World* InOwningWorld);

	void Update(float DeltaTime);

	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess) override;

	virtual void UnPossessCharacter() override;

	void MoveEnemy();
protected:

	virtual void Initialize() override;

private:

	void CheckForTarget();
	void HandleAttack();

private:
	Vector2 StartPosition = {};

	std::weak_ptr<Character> Target;
	std::weak_ptr<Enemy> ControlledEnemy;


	int VelocityUpdateCounter = 0;
	int VelocityMaxUpdateCounter = 120;

	float PullRange = 200.f;
	bool IsPulled = false;

	bool CanAttack = true;
	float AttackCooldown = 1.f;

	Coroutine Attack();
};