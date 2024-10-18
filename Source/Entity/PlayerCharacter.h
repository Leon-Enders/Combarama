#pragma once
#include "Character.h"
#include "../Render/Sword.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(const Vector2& InPosition);
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

	void Attack();


	void UpdateVelocity(const Vector2& NewVelocity);
	void ReceiveMouseInput(const Vector2& TargetPosition);

protected:
	virtual void UpdatePosition(float DeltaTime)override;
	virtual void UpdateRotation() override;

	float RotationSpeed = 10.f;
	float DesiredRotation = 0.f;
	

	float AttackSpeed = 1.f;
	float SwordRotation = 0.f;
	float DesiredSwordRotation = 0.f;

	int CurrentAttackFrame = 0;
	int AttackResetCounter = 60;

	bool IsAttacking = false;
	std::unique_ptr<Sword> RenderedSword;
};