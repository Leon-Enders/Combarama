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


//TODO: Refactor Attack functionality and Sword Transform handling
PlayerCharacter::PlayerCharacter(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Sword = GetWorld()->SpawnActor<Weapon>(InTransform);
}


void PlayerCharacter::Initialize()
{
	Character::Initialize();

	HeadColor = COLOR_LIGHTBLUE;
	BodyColor = COLOR_BLUE;

	Avatar::SetColor(BodyColor, HeadColor, CharacterRenderComponent.get());
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
		
		if (auto SwordSharedPtr = Sword.lock())
		{
			Sword.lock()->SetRotation(EntityTransform.Rotation);
		}
	}
	else
	{
		// Increment AttackFrameCounter
		CurrentAttackFrame++;
		if (auto SwordSharedPtr = Sword.lock())
		{
			// Handle AttackWindow
			if (ComboramaMath::FIsSame(SwordRotation, DesiredSwordRotation, 0.01f))
			{
				CurrentAttackFrame = 0;
				IsAttacking = false;

				// Reset Sword Rotation
				SwordSharedPtr->SetRotation(EntityTransform.Rotation);
				SwordSharedPtr->GetRenderComponent()->SetRenderActive(false);
				return;
			}

			float SwordLerpTime = DeltaTime * CurrentAttackFrame * AttackSpeed;
			float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

			//// Handle Sword Rotation
			SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);
			SwordSharedPtr->SetRotation(SwordRotation);
		}
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
	
	if (auto SwordSharedPtr = Sword.lock())
	{
		DealDamageInCone();

		SwordSharedPtr->GetRenderComponent()->SetRenderActive(true);
		IsAttacking = true;
		SwordRotation = -1.25f + EntityTransform.Rotation;
		DesiredSwordRotation = 1.25f + EntityTransform.Rotation;
	}
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
	auto SpawnedProjectilePtr = GetWorld()->SpawnActor<Projectile>(EntityTransform);

	// tell the projectile who spawned it
	if (auto SharedProjectilePtr = SpawnedProjectilePtr.lock())
	{
		SharedProjectilePtr->SetInstigator(shared_from_this());
	}
}

void PlayerCharacter::DealDamageInCone()
{
	std::vector<Collider> OverlappedColliders = CollisionSystem::Get().GetColliderInCone(shared_from_this(), GetForwardVector(), 135.f, 1.f);
	
	for (auto& OverlappedCollider : OverlappedColliders)
	{
		if (auto sOtherCharacter = std::dynamic_pointer_cast<Character>(OverlappedCollider.GetOwningActor().lock()))
		{
			sOtherCharacter->TakeDamage(5);
		}
	}
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Character::UpdatePosition(DeltaTime);

	//Update the Sword Position with the owning Players Position
	//TODO: Create a system in which you can attach actors to actors, so you dont have to manual update the transform
	if (auto SwordSharedPtr = Sword.lock())
	{
		SwordSharedPtr->SetPosition(EntityTransform.Position);
	}
	
}

void PlayerCharacter::UpdateRotation()
{
	 
}
