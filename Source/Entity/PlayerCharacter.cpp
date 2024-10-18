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
		
	
	//TODO: DeltaTime should be in s
	float DeltaTimeMS = DeltaTime / 1000.f;

	if (!IsAttacking)
	{
		if (ComboramaMath::FIsSame(Rotation, DesiredRotation, 0.01f))
		{
			Rotation = DesiredRotation;
			return;
		}

		Rotation = ComboramaMath::Slerpf(Rotation, DesiredRotation, DeltaTimeMS * RotationSpeed);

		OwnedRenderComponent->UpdateRotation(Rotation);
		RenderedSword->GetRenderComponent()->UpdateRotation(Rotation);
	}
	else
	{
		// Handle AttackWindow
		
		CurrentAttackReset += 1;
		if (CurrentAttackReset >= AttackResetCounter)
		{
			CurrentAttackReset = 0;
			IsAttacking = false;
			RenderedSword->GetRenderComponent()->UpdateRotation(DesiredSwordRotation);
			return;
		}

		//SDL_Log("SwordRotation: %f", SwordRotation);
		//SDL_Log("DesiredSwordRotation: %f", SwordRotation);
		//
		////// Handle Sword Rotation
		//
		//SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, DeltaTimeMS * RotationSpeed);
		//
		//RenderedSword->GetRenderComponent()->UpdateRotation(SwordRotation);
	}
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;

	
	IsAttacking = true;
	
	SwordRotation = 0.78f;
	SwordOriginalRotation = SwordRotation * -1.f;


	DesiredSwordRotation = -0.78f;
	RenderedSword->GetRenderComponent()->UpdateRotation(SwordRotation);
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Actor::UpdatePosition(DeltaTime);

	RenderedSword->GetRenderComponent()->UpdatePosition(Position);
}

void PlayerCharacter::UpdateRotation()
{

}
