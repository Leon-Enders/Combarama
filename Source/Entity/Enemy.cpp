#include "Enemy.h"
#include "../Utility/ColorHelper.h"
#include "../World/World.h"
#include "../Entity/Weapon.h"
#include "../Render/Avatar.h"
#include "../Math/ComboramaMath.h"
#include "../Entity/PlayerCharacter.h"
#include "../System/CollisionSystem.h"


Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Sword = GetWorld()->SpawnActor<Weapon>(InTransform);
}

void Enemy::Initialize()
{
	Character::Initialize();

	Speed = 125.f;

	HeadColor = COLOR_LIGHTYELLOW;
	BodyColor = COLOR_YELLOW;

	Avatar::SetColor(COLOR_YELLOW, COLOR_LIGHTYELLOW, CharacterRenderComponent.get());
}

void Enemy::Update(float DeltaTime)
{
	Character::Update(DeltaTime);

	float LerpTime = DeltaTime * RotationSpeed;

	float ClampedLerpTime = ComboramaMath::Clamp(LerpTime, LerpTime, 1.f);


	if (!IsAttacking)
	{

		EntityTransform.Rotation = ComboramaMath::Slerpf(EntityTransform.Rotation, DesiredRotation, ClampedLerpTime);
		
		if (auto SwordSharedPtr = Sword.lock())
		{
			SwordSharedPtr->SetRotation(EntityTransform.Rotation);
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

void Enemy::FixedUpdate(float FixedDeltaTime)
{
	Character::FixedUpdate(FixedDeltaTime);

	if (auto SwordSharedPtr = Sword.lock())
	{
		SwordSharedPtr->SetPosition(EntityTransform.Position);
	}
}

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity * Speed;
}

void Enemy::Attack()
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
	if (auto sSword = Sword.lock())
	{
		sSword->Destroy();
	}
}
