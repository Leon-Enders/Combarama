#pragma once
#include "MovementComponent.h"

class Character;

class CharacterMovementComponent : public MovementComponent
{
public:
	CharacterMovementComponent(Actor* Owner);
	virtual void Update(float DeltaTime);

private:
	Character* OwningCharacter = nullptr;
	float MovementSpeed = 250.f;
};