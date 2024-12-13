#include "Projectile.h"
#include "Character/Character.h"
#include "../../../RenderCore/Misc/PrimitiveHelpers.h"
#include "../../../RenderCore/Misc/ColorHelper.h"
#include "../Component/PrimitiveComponent.h"


Projectile::Projectile(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	//TODO: Make these verts static so they dont have to be generated each time a projectile is spawned
	std::vector<SDL_Vertex> CircleTriangles;
	Circle NewCircle = Circle(ProjectileSize);
	NewCircle.GetVerts(CircleTriangles);

	ProjectilePrimitive = CreateComponent<PrimitiveComponent>(std::move(CircleTriangles));
	ProjectilePrimitive->SetColor(COLOR_GREEN);
}

void Projectile::Initialize()
{
	Actor::Initialize();

	ProjectileCollider = std::make_shared<Collider>(shared_from_this(), ProjectileSize * 2.f, ProjectileSize * 2.f);
	ProjectileCollider->Initialize();
	ProjectileCollider->OnOverlapBeginDelegate.BindMemberFunction(shared_from_this(), &Projectile::OnOverlapBegin);

	Velocity = GetForwardVector() * ProjectileSpeed;
}

void Projectile::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
}

void Projectile::FixedUpdate(float FixedDeltaTime)
{
	Actor::FixedUpdate(FixedDeltaTime);

	UpdatePosition(FixedDeltaTime);

	LifeTime -= FixedDeltaTime;
	if (LifeTime < 0.f)
	{
		Destroy();
	}
}

void Projectile::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Projectile::OnOverlapBegin(std::weak_ptr<Collider> OtherCollider)
{
	if (auto sOtherCollider = OtherCollider.lock())
	{
		if (sOtherCollider->GetOwningActor().lock() == GetInstigator().lock()) return;

		if (auto sOtherCharacter = std::dynamic_pointer_cast<Character>(sOtherCollider->GetOwningActor().lock()))
		{
			sOtherCharacter->TakeDamage(ProjectileDamage);
		}

		Destroy();
	}
}

void Projectile::UpdatePosition(float DeltaTime)
{
	Vector2 NewPosition = Velocity * DeltaTime + GetPosition();
	SetPosition(NewPosition);
}
