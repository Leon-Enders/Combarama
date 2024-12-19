#include "CharacterMovementComponent.h"
#include "../../GameObject/Character/Character.h"

CharacterMovementComponent::CharacterMovementComponent(Actor* Owner, PrimitiveComponent* CollisionPrimitive)
	:
	MovementComponent(Owner, CollisionPrimitive),
	OwningCharacter(dynamic_cast<Character*>(Owner))
{
}

void CharacterMovementComponent::Update(float DeltaTime)
{
	Vector2 InputVector = OwningCharacter->ConsumeInputVector();
	Vector2 DeltaMove = InputVector * DeltaTime * MovementSpeed;

	if (DeltaMove != Vector2::Zero()) MoveUpdatedComponent(DeltaMove, true);
}
