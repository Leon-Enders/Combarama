#pragma once
#include "MovementComponent.h"

class Character;

class CharacterMovementComponent : public MovementComponent
{
public:
	CharacterMovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive);
	virtual void Update(float DeltaTime);

protected:

private:
	Character* OwningCharacter = nullptr;
	float MovementSpeed = 250.f;
};