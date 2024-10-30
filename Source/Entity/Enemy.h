#pragma once
#include "Character.h"
#include "../Utility/ColorHelper.h"

class Weapon;

class Enemy : public Character
{
public:
	Enemy(World* GameWorld);
	Enemy(World* GameWorld, const Transform& InTransform);
	virtual ~Enemy() = default;


	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	void UpdateVelocity(const Vector2& NewVelocity);
	void Attack();
	void DealDamageInCone();

	float DesiredRotation = 0.f;
protected:

private:



	float RotationSpeed = 20.f;
	


	float AttackSpeed = 1.f;
	float SwordRotation = 0.f;
	float DesiredSwordRotation = 0.f;

	int CurrentAttackFrame = 0;
	int AttackResetCounter = 60;

	bool IsAttacking = false;
	Weapon* Sword = nullptr;
};