#pragma once
#include "../ActorComponent.h"

class Character;

class MovementComponent : public ActorComponent
{
public:
	MovementComponent(Actor* Owner);
	virtual void Update(float DeltaTime);

protected:
	void MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep = false);
};