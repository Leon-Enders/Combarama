#pragma once
#include "../ActorComponent.h"

class PrimitiveComponent;
class Character;

class MovementComponent : public ActorComponent
{
public:
	MovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive);
	virtual void Update(float DeltaTime);

protected:
	void MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep = false);

	//INFO: Temp Solution
	PrimitiveComponent* CollisionPrimitive;
};