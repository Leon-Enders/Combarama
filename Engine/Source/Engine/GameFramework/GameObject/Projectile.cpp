#include "Projectile.h"
#include "Character/Character.h"
#include "../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../../../RenderCore/Misc/ColorHelper.h"
#include "../Component/PrimitiveComponent.h"
#include "../Component/MovementComponent/ProjectileMovementComponent.h"


Projectile::Projectile(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	ProjectilePrimitive = CreateComponent<PrimitiveComponent>(std::move(CirclePrimitive::Make(ProjectileSize)));
	ProjectilePrimitive->AttachToComponent(GetRootComponent());
	ProjectilePrimitive->SetColor(COLOR_GREEN);
	ProjectilePrimitive->SetCollisionShape(CollisionShape::MakeCircle(ProjectileSize));

	MovementComponent = CreateComponent<ProjectileMovementComponent>();
}

void Projectile::Initialize()
{
	Actor::Initialize();
}

void Projectile::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
}

void Projectile::FixedUpdate(float FixedDeltaTime)
{
	Actor::FixedUpdate(FixedDeltaTime);

	LifeTime -= FixedDeltaTime;
	if (LifeTime < 0.f)
	{
		Destroy();
	}
}
