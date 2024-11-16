#pragma once
#include "Character.h"
#include "../Coroutine/Awaitable/WaitSeconds.h"

class Weapon;

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(World* GameWorld, const Transform& InTransform);
	virtual ~PlayerCharacter()=default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	virtual void DrawDebug() override;



	//CombatInterface or CombatComponent
	void Attack();
	void Dash();
	void Shoot();
	void DealDamageInCone();

	void UpdateVelocity(const Vector2& NewVelocity);
	void ReceiveMouseInput(const Vector2& TargetPosition);

protected:
	virtual void UpdatePosition(float DeltaTime)override;
	virtual void UpdateRotation() override;

	virtual void OnCharacterDeath()override;



private:
	float RotationSpeed = 20.f;
	float DesiredRotation = 0.f;
	
	Vector2 LastMoveInput = {};




	//Attack
	float AttackSpeed = 1.f;
	float SwordRotation = 0.f;
	float DesiredSwordRotation = 0.f;

	int CurrentAttackFrame = 0;
	int AttackResetCounter = 60;

	bool IsAttacking = false;

	std::weak_ptr<Weapon> Sword;




	//Dash
	bool IsDashing = false;
	float DashSpeed = 1800.f;
	int CurrentDashFrame = 0;
	int DashResetcounter = 15;


private:

	Coroutine ActivateDashCooldown()
	{
		IsDashing = true;
		co_await WaitSeconds(0.1f, this);
		Velocity = Vector2::Zero();
		co_await WaitSeconds(1.f, this);
		IsDashing = false;
	}
};