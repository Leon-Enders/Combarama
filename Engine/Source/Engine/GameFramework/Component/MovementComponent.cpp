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
	Vector2 InputVector = OwningCharacter->ConsumeInputVector();
	Vector2 DeltaMove = InputVector * DeltaTime * MovementSpeed;

	MoveUpdatedComponent(DeltaMove);
}

void MovementComponent::MoveUpdatedComponent(const Vector2& DeltaMove, bool Sweep)
{
	if (!Sweep)
	{
		OwningCharacter->SetPosition(OwningCharacter->GetPosition()+DeltaMove);
	}
	
}
