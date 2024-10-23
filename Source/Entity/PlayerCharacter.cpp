#include "PlayerCharacter.h"
#include "../Utility/ColorHelper.h"
#include "../Utility/MathConstants.h"
#include "../Math/ComboramaMath.h"
#include "../Render/Avatar.h"
#include "Weapon.h"
#include "../World/World.h"

PlayerCharacter::PlayerCharacter(World* GameWorld)
	:
	Character(GameWorld)
{
	Initialize();
}

//TODO: Refactor Attack functionality and Sword Transform handling
PlayerCharacter::PlayerCharacter(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Sword = GetWorld()->SpawnActor<Weapon>();

	Initialize();
}

void PlayerCharacter::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{
	Vector2 DeltaPosition = EntityTransform.Position - TargetPosition;
	float AngleInRad = std::atan2f(DeltaPosition.X, -DeltaPosition.Y);

	

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
	SwordRotation = -1.25f + EntityTransform.Rotation;

	DesiredSwordRotation = 1.25f + EntityTransform.Rotation;
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
