#include "PlayerCharacter.h"
#include "../Utility/ColorHelper.h"
#include "../Utility/MathConstants.h"
#include "../Math/ComboramaMath.h"
#include "../Render/Avatar.h"

//TODO: Refactor Attack functionality and Sword Transform handling
PlayerCharacter::PlayerCharacter(const Transform& InTransform)
	:
	Character(InTransform)
{
	Sword = std::make_unique<Weapon>(InTransform);
}

void PlayerCharacter::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{
	Vector2 DeltaPosition = EntityTransform.Position - TargetPosition;
	float AngleInRad = std::atan2f(DeltaPosition.X, DeltaPosition.Y);

	DesiredRotation = AngleInRad;
	
}

void PlayerCharacter::Initialize()
{
	Avatar::SetColor(COLOR_BLUE, COLOR_LIGHTBLUE, CharacterRenderComponent.get());
}

void PlayerCharacter::Update(float DeltaTime)
{
	Character::Update(DeltaTime);
		

	float LerpTime = DeltaTime * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);


	if (!IsAttacking)
	{
		if (ComboramaMath::FIsSame(EntityTransform.Rotation, DesiredRotation, 0.01f))
		{
			EntityTransform.Rotation = DesiredRotation;
			return;
		}

		EntityTransform.Rotation = ComboramaMath::Slerpf(EntityTransform.Rotation, DesiredRotation, ClampedLerpTime);
		Sword->SetRotation(EntityTransform.Rotation);
	}
	else
	{
		// Increment AttackFrameCounter
		CurrentAttackFrame++;

		// Handle AttackWindow
		if (ComboramaMath::FIsSame(SwordRotation, DesiredSwordRotation, 0.01f))
		{
			CurrentAttackFrame = 0;
			IsAttacking = false;

			// Reset Sword Rotation
			Sword->SetRotation(EntityTransform.Rotation);
			Sword->GetRenderComponent()->SetRenderActive(false);
			return;
		}
		
		float SwordLerpTime = DeltaTime * CurrentAttackFrame * AttackSpeed;
		float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

		//// Handle Sword Rotation
		SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);
		Sword->SetRotation(SwordRotation);
		
	}
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;

	Sword->GetRenderComponent()->SetRenderActive(true);
	IsAttacking = true;
	SwordRotation = 1.25f+EntityTransform.Rotation;

	DesiredSwordRotation = -1.25f + EntityTransform.Rotation;
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Character::UpdatePosition(DeltaTime);

	//Update the Sword Position with the owning Players Position
	//TODO: Create a system in which you can attach actors to actors, so you dont have to manual update the transform
	Sword->SetPosition(EntityTransform.Position);
}

void PlayerCharacter::UpdateRotation()
{

}
