#pragma once
#include "Character.h"

class Weapon;

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(World* GameWorld);
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

	float RotationSpeed = 20.f;
	float DesiredRotation = 0.f;
	

	float AttackSpeed = 1.f;
	float SwordRotation = 0.f;
	float DesiredSwordRotation = 0.f;

	int CurrentAttackFrame = 0;
	int AttackResetCounter = 60;

	bool IsAttacking = false;

	Weapon* Sword = nullptr;


	bool IsDashing = false;


	float DashSpeed = 1800.f;
	int CurrentDashFrame = 0;
	int DashResetcounter = 15;


private:
};