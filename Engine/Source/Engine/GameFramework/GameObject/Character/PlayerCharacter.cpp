#include "PlayerCharacter.h"
#include <numbers>
#include "../../../../Core/Math/ComboramaMath.h"
#include "../../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../Projectile.h"
#include "../../World/World.h"
#include "../../../../RenderCore/Misc/DrawDebugHelpers.h"
#include "../../Component/PrimitiveComponent.h"
#include "../../Component/CameraComponent.h"



//TODO: Refactor Attack functionality and Sword Transform handling
PlayerCharacter::PlayerCharacter(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Weapon = CreateComponent<PrimitiveComponent>(std::move(SwordPrimitive::Make({ { 75.f,0.f }, 1.5708f, { 1.f,1.f } })));
	Weapon->AttachToComponent(GetRootComponent());
	Weapon->SetColor(COLOR_GREY);
	Weapon->SetRenderActive(false);

	PlayerCam = CreateComponent<CameraComponent>();
	PlayerCam->AttachToComponent(GetRootComponent());

	HeadColor = COLOR_LIGHTBLUE;
	BodyColor = COLOR_BLUE;

	SetColor(BodyColor, HeadColor);
}


void PlayerCharacter::Initialize()
{
	Character::Initialize();

}

void PlayerCharacter::Update(float DeltaTime)
{
	Character::Update(DeltaTime);
	

	
	float LerpTime = DeltaTime * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);

	
	if (!IsAttacking)
	{

		float NewRotation = ComboramaMath::Slerpf(GetRotation(), GetController()->GetControlRotation(), ClampedLerpTime);
		SetRotation(NewRotation);
	}
	else
	{
		// Increment AttackFrameCounter
		CurrentAttackFrame++;
		if (Weapon)
		{

			// Handle AttackWindow
			if (ComboramaMath::FIsSame(SwordRotation, DesiredSwordRotation, 0.01f))
			{
				CurrentAttackFrame = 0;
				IsAttacking = false;

				// Reset Sword Rotation
				Weapon->SetRotation(0.f);
				Weapon->SetRenderActive(false);
				return;
			}

			float SwordLerpTime = DeltaTime * CurrentAttackFrame * AttackSpeed;
			float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

			//// Handle Sword Rotation
			SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);
			Weapon->SetRotation(SwordRotation);
		}
	}
}

void PlayerCharacter::FixedUpdate(float FixedDeltaTime)
{
	Character::FixedUpdate(FixedDeltaTime);
	
}

void PlayerCharacter::DrawDebug()
{
	//DrawDebugHelpers::Get().DrawDebugCone(GetPosition(), GetForwardVector(), 135.f, 1.f);
}

void PlayerCharacter::Attack()
{
	if (IsAttacking) return;
	
	if (Weapon)
	{
		DealDamageInCone();

		IsAttacking = true;
		SwordRotation = -1.25f;
		DesiredSwordRotation = 1.25f;
		Weapon->SetRotation(SwordRotation);
		Weapon->SetRenderActive(true);
	}
}

void PlayerCharacter::Dash()
{
	if (!IsDashing)
	{
		ActivateDashCooldown();
	}
}

void PlayerCharacter::Shoot()
{
	auto SpawnedProjectilePtr = GetWorld()->SpawnGameObject<Projectile>(GetTransform());

	// tell the projectile who spawned it
	if (auto sProjectilePtr = SpawnedProjectilePtr.lock())
	{
		sProjectilePtr->SetInstigator(shared_from_this());
	}
}

void PlayerCharacter::DealDamageInCone()
{
	std::vector<Actor*> OverlappingActors = GetWorld()->GetAllActorsInCone(shared_from_this(), GetForwardVector(), 135.f, 1.f);
	
	for (auto& OtherActor : OverlappingActors)
	{
		if (auto OtherCharacter = dynamic_cast<Character*>(OtherActor))
		{
			OtherCharacter->TakeDamage(5);
		}
	}
}

void PlayerCharacter::OnCharacterDeath()
{
}

Coroutine PlayerCharacter::Spray()
{

	for (int i = 0; i < 10; i++)
	{
		auto SpawnedProjectilePtr = GetWorld()->SpawnGameObject<Projectile>(GetTransform());

		// tell the projectile who spawned it
		if (auto sProjectilePtr = SpawnedProjectilePtr.lock())
		{
			sProjectilePtr->SetInstigator(shared_from_this());
		}

		co_await WaitSeconds(0.1f, this);
	}
}
