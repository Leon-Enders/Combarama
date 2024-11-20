#include "Enemy.h"
#include "../../Utility/ColorHelper.h"
#include "../../World/World.h"
#include "../../PrimitiveFactory/Avatar.h"
#include "../../Math/ComboramaMath.h"
#include "../Character/PlayerCharacter.h"
#include "../../System/CollisionSystem.h"
#include "../../Component/PrimitiveComponent.h"
#include "../../Component/WeaponComponent.h"


Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Weapon = CreateComponent<WeaponComponent>();
	Weapon->SetTransform({ {75.f,0.f},1.5708f,{1.f,1.f} });
	Weapon->SetColor(COLOR_GREY);

}

void Enemy::Initialize()
{
	Character::Initialize();

	Speed = 125.f;

	HeadColor = COLOR_LIGHTYELLOW;
	BodyColor = COLOR_YELLOW;

	Avatar::SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW, GetCharacterPrimitive());
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
			Weapon->SetRotation(GetRotation());
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
				Weapon->SetRotation(GetRotation());
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

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity * Speed;
}

void Enemy::Attack()
{
	if (IsAttacking) return;

	if (Weapon)
	{
		DealDamageInCone();

		Weapon->SetRenderActive(true);
		IsAttacking = true;
		SwordRotation = -1.25f + GetRotation();
		DesiredSwordRotation = 1.25f + GetRotation();
	}
}

void Enemy::DealDamageInCone()
{
	std::vector<Collider> OverlappedColliders = CollisionSystem::Get().GetColliderInCone(shared_from_this(), GetForwardVector(), 135.f, 1.f);

	for (auto& OverlappedCollider : OverlappedColliders)
	{
		if (auto sOtherCharacter = std::dynamic_pointer_cast<Character>(OverlappedCollider.GetOwningActor().lock()))
		{
			sOtherCharacter->TakeDamage(2);
		}
	}
}

void Enemy::OnCharacterDeath()
{
	
}