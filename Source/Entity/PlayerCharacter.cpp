#include "PlayerCharacter.h"
#include <numbers>
#include "../Utility/ColorHelper.h"
#include "../Math/ComboramaMath.h"
#include "../Render/Avatar.h"
#include "Projectile.h"
#include "Weapon.h"
#include "../World/World.h"
#include "../Utility/DrawDebugHelpers.h"
#include "../System/CollisionSystem.h"

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
	if (!IsDashing)
	{
		LastMoveInput = NewVelocity.Normalize();
		Velocity = LastMoveInput * Speed;
	}
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{
	Vector2 DeltaPosition =  TargetPosition - EntityTransform.Position;
	float AngleInRad = std::atan2f(DeltaPosition.Y, DeltaPosition.X);
	
	

	DesiredRotation = AngleInRad;
	
}

void PlayerCharacter::Initialize()
{
	HeadColor = COLOR_LIGHTBLUE;
	BodyColor = COLOR_BLUE;

	Avatar::SetColor(BodyColor, HeadColor, CharacterRenderComponent.get());
}

void PlayerCharacter::Update(float DeltaTime)
{
	Character::Update(DeltaTime);
	
	if (IsDashing)
	{
		CurrentDashFrame++;
		if (CurrentDashFrame > DashResetcounter)
		{
			CurrentDashFrame = 0;
			IsDashing = false;
			Velocity = Vector2::Zero();
		}
	}

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

void PlayerCharacter::FixedUpdate(float FixedDeltaTime)
{
	Character::FixedUpdate(FixedDeltaTime);
	
}

void PlayerCharacter::DrawDebug()
{
	DrawDebugHelpers::Get().DrawDebugCone(EntityTransform.Position, { cos(EntityTransform.Rotation), sin(EntityTransform.Rotation) }, 135.f, 1.f);
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;
	
	DealDamageInCone();

	Sword->GetRenderComponent()->SetRenderActive(true);
	IsAttacking = true;
	SwordRotation = -1.25f + EntityTransform.Rotation;
	DesiredSwordRotation = 1.25f + EntityTransform.Rotation;
}

void PlayerCharacter::Dash()
{
	if (!IsDashing)
	{
		IsDashing = true;
		//Velocity = GetForwardVector() * DashSpeed;
		Velocity = LastMoveInput * DashSpeed;
	}
}

void PlayerCharacter::Shoot()
{
	GetWorld()->SpawnActor<Projectile>(EntityTransform);
}

void PlayerCharacter::DealDamageInCone()
{
	std::vector<Collider> OverlappedColliders = CollisionSystem::Get().GetColliderInCone(this, GetForwardVector(), 135.f, 1.f);
	
	for (auto& OverlappedCollider : OverlappedColliders)
	{
		if (Character* OtherCharacter = dynamic_cast<Character*>(OverlappedCollider.GetOwningActor()))
		{
			OtherCharacter->TakeDamage(5);
		}
	}

	
	
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
