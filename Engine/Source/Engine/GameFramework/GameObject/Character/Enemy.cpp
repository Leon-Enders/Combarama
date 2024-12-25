#include "Enemy.h"
#include "../../../../RenderCore/Misc/ColorHelper.h"
#include "../../World/World.h"
#include "../../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../../../../Core/Math/ComboramaMath.h"
#include "../Character/PlayerCharacter.h"
#include "../../Component/PrimitiveComponent.h"



Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Weapon = CreateComponent<PrimitiveComponent>(std::move(SwordPrimitive::Make({ { 75.f,0.f }, 1.5708f, { 1.f,1.f } })));
	Weapon->AttachToComponent(GetRootComponent());
	Weapon->SetColor(COLOR_GREY);
	Weapon->SetRenderActive(false);
}

void Enemy::Initialize()
{
	Character::Initialize();

	HeadColor = COLOR_LIGHTYELLOW;
	BodyColor = COLOR_YELLOW;

	SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW);
}

void Enemy::Update(float DeltaTime)
{
	Character::Update(DeltaTime);

	float LerpTime = DeltaTime * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);


	if (!IsAttacking)
	{

		float NewRotation = ComboramaMath::Slerpf(GetRotation(), GetController()->GetControlRotation(), ClampedLerpTime);
		SetRotation(NewRotation);

		if (Weapon)
		{
			Weapon->SetRotation(0.f);
		}
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

void Enemy::FixedUpdate(float FixedDeltaTime)
{
	Character::FixedUpdate(FixedDeltaTime);

}

void Enemy::Attack()
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

void Enemy::DealDamageInCone()
{
	std::vector<Actor*> OverlappingActors = GetWorld()->GetAllActorsInCone(shared_from_this(), GetForwardVector(), 135.f, 1.f);

	for (auto& OtherActor : OverlappingActors)
	{
		if (auto OtherCharacter = dynamic_cast<Character*>(OtherActor))
		{
			OtherCharacter->TakeDamage(1);
		}
	}
}

void Enemy::OnCharacterDeath()
{
	
}