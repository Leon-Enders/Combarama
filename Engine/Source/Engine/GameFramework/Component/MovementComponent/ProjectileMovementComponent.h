#pragma once
#include "MovementComponent.h"

class ProjectileMovementComponent : public MovementComponent
{
public:
	ProjectileMovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive);
	virtual void Update(float DeltaTime);

	void SetProjectileSpeed(float Speed) { ProjectileSpeed = Speed; }
private:
	Vector2 MoveDirection;
	float ProjectileSpeed = 1000.f;
};
