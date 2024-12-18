#pragma once
#include "ActorComponent.h"

class Character;

class MovementComponent : public ActorComponent
{
public:
	MovementComponent();
	virtual ~MovementComponent();
	virtual void Update(float DeltaTime);

	void MoveUpdatedComponent(const Vector2& DeltaMove);
private:
	Character* OwningCharacter = nullptr;
};