#pragma once
#include "ActorComponent.h"

class Character;

class MovementComponent : public ActorComponent
{
public:
	MovementComponent(Actor* Owner);
	virtual ~MovementComponent();
	virtual void Update(float DeltaTime);

	void MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep = false);
private:
	Character* OwningCharacter = nullptr;
	float MovementSpeed = 250.f;
};