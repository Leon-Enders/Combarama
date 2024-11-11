#pragma once
#include <memory>
#include "Controller.h"
#include "../Entity/Enemy.h"
#include "../Coroutine/Task.h"
#include "../Coroutine/Awaitable/WaitSeconds.h"


class AIController : public Controller, public std::enable_shared_from_this<AIController>
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

	bool CanAttack = true;
	float AttackCooldown = 1.f;


	Task ActivateAttackCooldown()
	{
		CanAttack = false;
		co_await WaitSeconds(AttackCooldown);
		CanAttack = true;
	}

};