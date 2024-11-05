#include "Enemy.h"
#include "../Utility/ColorHelper.h"
#include "../World/World.h"
#include "../Entity/Weapon.h"
#include "../Render/Avatar.h"
#include "../Math/ComboramaMath.h"
#include "../Entity/PlayerCharacter.h"
#include "../System/CollisionSystem.h"


Enemy::Enemy(World* GameWorld)
	:
	Character(GameWorld)
{
	Sword = GetWorld()->SpawnActor<Weapon>();
	Initialize();
}

Enemy::Enemy(World* GameWorld, const Transform& InTransform)
	:
	Character(GameWorld, InTransform)
{
	Sword = GetWorld()->SpawnActor<Weapon>();
	Initialize();
}

void Enemy::Initialize()
{
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
		Sword.lock()->SetRotation(EntityTransform.Rotation);
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
			Sword.lock()->SetRotation(EntityTransform.Rotation);
			Sword.lock()->GetRenderComponent()->SetRenderActive(false);
			return;
		}

		float SwordLerpTime = DeltaTime * CurrentAttackFrame * AttackSpeed;
		float ClampedSwordLerpTime = ComboramaMath::Clamp(SwordLerpTime, SwordLerpTime, 1.f);

		//// Handle Sword Rotation
		SwordRotation = ComboramaMath::Lerp(SwordRotation, DesiredSwordRotation, ClampedSwordLerpTime);
		Sword.lock()->SetRotation(SwordRotation);

	}
}

void Enemy::FixedUpdate(float FixedDeltaTime)
{
	Character::FixedUpdate(FixedDeltaTime);
	Sword.lock()->SetPosition(EntityTransform.Position);
}

void Enemy::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity * Speed;
}

void Enemy::Attack()
{
	if (IsAttacking) return;

	DealDamageInCone();

	Sword.lock()->GetRenderComponent()->SetRenderActive(true);
	IsAttacking = true;
	SwordRotation = -1.25f + EntityTransform.Rotation;
	DesiredSwordRotation = 1.25f + EntityTransform.Rotation;
}

void Enemy::DealDamageInCone()
{
	std::vector<Collider> OverlappedColliders = CollisionSystem::Get().GetColliderInCone(this, GetForwardVector(), 135.f, 1.f);

	for (auto& OverlappedCollider : OverlappedColliders)
	{
		if (PlayerCharacter* OtherCharacter = dynamic_cast<PlayerCharacter*>(OverlappedCollider.GetOwningActor()))
		{
			OtherCharacter->TakeDamage(1);
		}
	}
}
