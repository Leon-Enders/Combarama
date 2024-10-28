#pragma once
#include "Character.h"

class Weapon;

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(World* GameWorld);
	PlayerCharacter(World* GameWorld, const Transform& InTransform);
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	void Attack();


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

	std::unique_ptr<Collider> AttackCollider = nullptr;
};