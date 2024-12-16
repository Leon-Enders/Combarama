#include "Enemy.h"
#include "../../../../RenderCore/Misc/ColorHelper.h"
#include "../../World/World.h"
#include "../../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../../../../Core/Math/ComboramaMath.h"
#include "../Character/PlayerCharacter.h"
#include "../../../Physics/CollisionSystem.h"
#include "../../Component/PrimitiveComponent.h"



Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Weapon = CreateComponent<PrimitiveComponent>(std::move(Sword::Make({ { 75.f,0.f }, 1.5708f, { 1.f,1.f } })));
	Weapon->AttachToComponent(GetRootComponent());
	Weapon->SetColor(COLOR_GREY);
	Weapon->SetRenderActive(false);
}

void Enemy::Initialize()
{
	Character::Initialize();

	Speed = 125.f;

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

void Enemy::AddMoveInput(const Vector2& MoveInput)
{
	Velocity = MoveInput * Speed;
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