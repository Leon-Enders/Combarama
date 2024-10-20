#include "PlayerCharacter.h"
#include "../Utility/ColorHelper.h"
#include "../Utility/MathConstants.h"
#include "../Math/ComboramaMath.h"
#include "../Render/Avatar.h"
#include "../Render/Sword.h"


PlayerCharacter::PlayerCharacter(const Transform& InTransform)
	:
	Character(InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, InTransform);

	Transform SwordTransform = InTransform;
	SwordTransform.Position += {0.f, 100.f};

	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordTriangles), this);
	SwordRenderComponent->SetRenderActive(false);
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
		
	
	//TODO: DeltaTime should be in seconds
	float DeltaTimeS = DeltaTime / 1000.f;

	float LerpTime = DeltaTimeS * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);


	if (!IsAttacking)
	{
		if (ComboramaMath::FIsSame(EntityTransform.Rotation, DesiredRotation, 0.01f))
		{
			EntityTransform.Rotation = DesiredRotation;
			return;
		}

		EntityTransform.Rotation = ComboramaMath::Slerpf(EntityTransform.Rotation, DesiredRotation, ClampedLerpTime);
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
			SwordRenderComponent->SetRenderActive(false);
			return;
		}
		
		float SwordLerpTime = DeltaTimeS * CurrentAttackFrame * AttackSpeed;
		float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

		//// Handle Sword Rotation
		SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);

		
	}
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;

	SwordRenderComponent->SetRenderActive(true);
	IsAttacking = true;
	SwordRotation = 1.25f+EntityTransform.Rotation;

	DesiredSwordRotation = -1.25f + EntityTransform.Rotation;
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Character::UpdatePosition(DeltaTime);
}

void PlayerCharacter::UpdateRotation()
{

}
