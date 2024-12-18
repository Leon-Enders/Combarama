#include "MovementComponent.h"
#include "../../GameObject/Actor.h"
#include "../PrimitiveComponent.h"
#include "../../World/World.h"
#include "../../../../PhysicsCore/CollisionResult.h"

MovementComponent::MovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive)
	:
	ActorComponent(Owner),
	CollisionPrimitive(CollisionPrimitive)
{
}

void MovementComponent::Update(float DeltaTime)
{
}

void MovementComponent::MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep)
{
	Vector2 StartLocation = GetOwner()->GetPosition();
	Vector2 EndLocation = StartLocation + DeltaMove;
	if (!Sweep)
	{
		GetOwner()->SetPosition(EndLocation);
		return;
	}

	CollisionResult CResult;
	if (GetWorld()->SweepByChannel(StartLocation, EndLocation, CResult,CollisionPrimitive->GetCollisionShape(), ECollisionChannel::ECC_Visibility,GetOwner()))
	{
		GetOwner()->SetPosition(CResult.ImpactPoint);
	}
	

}
