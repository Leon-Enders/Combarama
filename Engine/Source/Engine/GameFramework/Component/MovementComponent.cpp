#include "MovementComponent.h"
#include "../GameObject/Character/Character.h"

MovementComponent::MovementComponent(Actor* Owner)
	:
	ActorComponent(Owner)
{
	OwningCharacter = static_cast<Character*>(Owner);
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(float DeltaTime)
{
}

void MovementComponent::MoveUpdatedComponent(const Vector2& DeltaMove)
{
}
