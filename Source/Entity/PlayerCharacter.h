#pragma once
#include "Character.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(const Vector2& InPosition);

	void UpdateVelocity(const Vector2& NewVelocity);
	void ReceiveMouseInput(const Vector2& TargetPosition);

protected:
	virtual void Initialize() override;
	virtual void UpdateRotation() override;


	Vector2 LastMousePosition = {0.f,0.f};
};