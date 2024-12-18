#include "MovementComponent.h"
#include "../../GameObject/Actor.h"

MovementComponent::MovementComponent(Actor* Owner)
	:
	ActorComponent(Owner)
{
}

void MovementComponent::Update(float DeltaTime)
{
}

void MovementComponent::MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep)
{
	if (!Sweep)
	{
		GetOwner()->SetPosition(GetOwner()->GetPosition() + DeltaMove);
	}
	
}
