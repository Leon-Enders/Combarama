#include "Weapon.h"
#include "../Render/Sword.h"

Weapon::Weapon(World* GameWorld)
	:
	Actor(GameWorld)
{
}

Weapon::Weapon(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, InTransform);

	EntityTransform.Position += WeaponOffset;

	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordTriangles), this);
	SwordRenderComponent->SetRenderActive(false);
}
