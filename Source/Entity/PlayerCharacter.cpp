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
	if (IsAttacking) return;

	float DeltaX = Position.X - TargetPosition.X;
	float DeltaY = Position.Y - TargetPosition.Y;

	float AngleInRad = std::atan2f(DeltaX, DeltaY);

	DesiredRotation = AngleInRad;
}

void PlayerCharacter::Initialize()
{
	SetColor(COLOR_BLUE, COLOR_LIGHTBLUE);
}

void PlayerCharacter::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
	
	if (IsAttacking)
	{
		CurrentAttackReset += 1;
		if (CurrentAttackReset >= AttackResetCounter)
		{
			CurrentAttackReset = 0;
			IsAttacking = false;
		}
		return;
	}
		
	
	//TODO: DeltaTime should be in s
	float DeltaTimeMS = DeltaTime / 1000.f;

	if (ComboramaMath::FIsSame(Rotation, DesiredRotation, 0.01f))
	{
		Rotation = DesiredRotation;
		return;
	}

	float CachedRotation = Rotation;	
	Rotation = ComboramaMath::Slerpf(Rotation, DesiredRotation, DeltaTimeMS * RotationSpeed);
	
	float DeltaRotation = CachedRotation - Rotation;


	OwnedRenderComponent->UpdateRotation(DeltaRotation);
	RenderedSword->GetRenderComponent()->UpdateRotation(DeltaRotation);
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;

	IsAttacking = true;




}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Actor::UpdatePosition(DeltaTime);

	RenderedSword->GetRenderComponent()->UpdatePosition(Position);
}

void PlayerCharacter::UpdateRotation()
{

}
