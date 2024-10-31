#include "Projectile.h"
#include "../Utility/PrimitiveHelpers.h"
#include "../Utility/ColorHelper.h"

Projectile::Projectile(World* GameWorld)
	:
	Actor(GameWorld)
{
	std::vector<SDL_Vertex> CircleTriangles;

	Circle NewCircle = Circle(ProjectileSize);

	NewCircle.GetVerts(CircleTriangles);


	ProjectileRenderComponent = std::make_unique<RenderComponent>(*this, std::move(CircleTriangles));
	ProjectileCollider = std::make_unique<Collider>(this, ProjectileSize * 2.f, ProjectileSize * 2.f);
	Initialize();
}

Projectile::Projectile(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> CircleTriangles;
	Circle NewCircle = Circle(ProjectileSize);
	NewCircle.GetVerts(CircleTriangles);


	ProjectileRenderComponent = std::make_unique<RenderComponent>(*this, std::move(CircleTriangles));
	ProjectileCollider = std::make_unique<Collider>(this, ProjectileSize*2.f, ProjectileSize * 2.f);
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
