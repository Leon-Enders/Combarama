#pragma once
#include "Character.h"
#include "../Render/Sword.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(const Vector2& InPosition);
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

	void UpdateVelocity(const Vector2& NewVelocity);
	void ReceiveMouseInput(const Vector2& TargetPosition);

protected:
	virtual void UpdatePosition(float DeltaTime)override;
	virtual void UpdateRotation() override;

	float RotationSpeed = 10.f;
	float DesiredRotation = 0.f;

	std::unique_ptr<Sword> RenderedSword;
};