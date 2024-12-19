#include "ProjectileMovementComponent.h"
#include "../../GameObject/Actor.h"

#include "../../../../PhysicsCore/Misc/CollisionHelper.h"


ProjectileMovementComponent::ProjectileMovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive)
	:
	MovementComponent(Owner,CollisionPrimitive)
{
	MoveDirection = GetOwner()->GetTransform().GetForwardVector();
}

void ProjectileMovementComponent::Update(float DeltaTime)
{
	Vector2 DeltaVector = MoveDirection * DeltaTime * ProjectileSpeed;
	MoveUpdatedComponent(DeltaVector);
}
