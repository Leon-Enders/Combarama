#include "Projectile.h"
#include "Character.h"
#include "../Utility/PrimitiveHelpers.h"
#include "../Utility/ColorHelper.h"

Projectile::Projectile(World* GameWorld)
	:
	Actor(GameWorld)
{

	using namespace std::placeholders;
	std::vector<SDL_Vertex> CircleTriangles;

	Circle NewCircle = Circle(ProjectileSize);

	NewCircle.GetVerts(CircleTriangles);


	ProjectileRenderComponent = std::make_unique<RenderComponent>(*this, std::move(CircleTriangles));
	ProjectileCollider = std::make_unique<Collider>(this, ProjectileSize * 2.f, ProjectileSize * 2.f);
	ProjectileCollider->OnCollisionEnterDelegate = std::bind(&Projectile::OnCollisionEnter, this, _1);
	Initialize();
}

Projectile::Projectile(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	using namespace std::placeholders;
	std::vector<SDL_Vertex> CircleTriangles;
	Circle NewCircle = Circle(ProjectileSize);
	NewCircle.GetVerts(CircleTriangles);


	ProjectileRenderComponent = std::make_unique<RenderComponent>(*this, std::move(CircleTriangles));
	ProjectileCollider = std::make_unique<Collider>(this, ProjectileSize*2.f, ProjectileSize * 2.f);
	ProjectileCollider->OnCollisionEnterDelegate = std::bind(&Projectile::OnCollisionEnter, this, _1);
	Initialize();
}

void Projectile::Initialize()
{
	ProjectileRenderComponent->SetColor(COLOR_GREEN);
	Velocity = GetForwardVector() * ProjectileSpeed;
}

void Projectile::Update(float DeltaTime)
{

}

void Projectile::FixedUpdate(float FixedDeltaTime)
{
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

void Projectile::UpdatePosition(float DeltaTime)
{
	EntityTransform.Position += Velocity * DeltaTime;
}

void Projectile::OnCollisionEnter(const Collider& Other)
{
	if (Other.GetOwningActor() == GetInstigator()) return;

	if (Character* OtherCharacter = dynamic_cast<Character*>(Other.GetOwningActor()))
	{
		OtherCharacter->TakeDamage(ProjectileDamage);
	}
}
