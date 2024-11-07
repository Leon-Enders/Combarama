#include "Projectile.h"
#include "Character.h"
#include "../Utility/PrimitiveHelpers.h"
#include "../Utility/ColorHelper.h"


Projectile::Projectile(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> CircleTriangles;
	Circle NewCircle = Circle(ProjectileSize);
	NewCircle.GetVerts(CircleTriangles);


	ProjectileRenderComponent = std::make_unique<RenderComponent>(*this, std::move(CircleTriangles));
	
	
}

void Projectile::Initialize()
{
	ProjectileCollider = std::make_shared<Collider>(shared_from_this(), ProjectileSize * 2.f, ProjectileSize * 2.f);
	ProjectileCollider->Initialize();
	ProjectileCollider->OnOverlapBeginDelegate.BindMemberFunction(shared_from_this(), &Projectile::OnOverlapBegin);

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
	EntityTransform.Position += Velocity * DeltaTime;
}
