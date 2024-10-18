#include "PlayerCharacter.h"
#include "../Utility/ColorHelper.h"
#include "../Utility/MathConstants.h"
#include "../Math/ComboramaMath.h"


PlayerCharacter::PlayerCharacter(const Vector2& InPosition)
	:
	Character(InPosition)
{
	Position = InPosition;

	//Construct a Sword
	RenderedSword = std::make_unique<Sword>(InPosition, Rotation, Vector2(0.f,100.f));
	RenderedSword->GetRenderComponent()->SetRenderActive(false);
}

void PlayerCharacter::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{

	float DeltaX = Position.X - TargetPosition.X;
	float DeltaY = Position.Y - TargetPosition.Y;

	float AngleInRad = std::atan2f(DeltaX, DeltaY);

	
	DesiredRotation = AngleInRad;
	//SDL_Log("Desired Rotation: %f", DesiredRotation);
	//SDL_Log("Rotation: %f", Rotation);
}

void PlayerCharacter::Initialize()
{
	SetColor(COLOR_BLUE, COLOR_LIGHTBLUE);
}

void PlayerCharacter::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
		
	
	//TODO: DeltaTime should be in seconds
	float DeltaTimeS = DeltaTime / 1000.f;

	float LerpTime = DeltaTimeS * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);


	if (!IsAttacking)
	{
		if (ComboramaMath::FIsSame(Rotation, DesiredRotation, 0.01f))
		{
			Rotation = DesiredRotation;
			return;
		}

		Rotation = ComboramaMath::Slerpf(Rotation, DesiredRotation, ClampedLerpTime);

		OwnedRenderComponent->UpdateRotation(Rotation);
		RenderedSword->GetRenderComponent()->UpdateRotation(Rotation);
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
			RenderedSword->GetRenderComponent()->UpdateRotation(Rotation);
			RenderedSword->GetRenderComponent()->SetRenderActive(false);
			return;
		}
		
		float SwordLerpTime = DeltaTimeS * CurrentAttackFrame * AttackSpeed;
		float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

		//// Handle Sword Rotation
		SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);

		
		RenderedSword->GetRenderComponent()->UpdateRotation(SwordRotation);
	}
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;

	RenderedSword->GetRenderComponent()->SetRenderActive(true);
	IsAttacking = true;
	SwordRotation = 1.25f+Rotation;

	DesiredSwordRotation = -1.25f +Rotation;
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Actor::UpdatePosition(DeltaTime);

	RenderedSword->GetRenderComponent()->UpdatePosition(Position);
}

void PlayerCharacter::UpdateRotation()
{

}
