#pragma once
#include "../ActorComponent.h"

class PrimitiveComponent;
class Character;
enum class ECollisionChannel;

class MovementComponent : public ActorComponent
{
public:
	MovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive);
	virtual void Update(float DeltaTime);


protected:
	void MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep = false, const ECollisionChannel& CollisionChannel = {});

	//INFO: Temp Solution
	PrimitiveComponent* CollisionPrimitive;
};