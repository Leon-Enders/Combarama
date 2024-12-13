#pragma once
#include "Character.h"
#include "../../Utility/ColorHelper.h"



class Enemy : public Character
{
public:
	Enemy(World* GameWorld, const Transform& InTransform);
	virtual ~Enemy() = default;


	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	void UpdateVelocity(const Vector2& NewVelocity);
	void SetSpeed(float NewSpeed) { Speed = NewSpeed; }

	void Attack();
	void DealDamageInCone();

protected:

	virtual void OnCharacterDeath() override;

private:
	float RotationSpeed = 20.f;

	float AttackSpeed = 1.f;
	float SwordRotation = 0.f;
	float DesiredSwordRotation = 0.f;

	int CurrentAttackFrame = 0;
	int AttackResetCounter = 60;

	bool IsAttacking = false;
	PrimitiveComponent* Weapon;
};