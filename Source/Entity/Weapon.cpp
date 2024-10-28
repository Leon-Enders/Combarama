#include "Weapon.h"
#include "../Render/Sword.h"

Weapon::Weapon(World* GameWorld)
	:
	Actor(GameWorld)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, LocalTransform);

	SwordRenderComponent = std::make_unique<RenderComponent>(*this, std::move(SwordTriangles));
	SwordRenderComponent->SetRenderActive(false);
}

Weapon::Weapon(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, LocalTransform);

	SwordRenderComponent = std::make_unique<RenderComponent>(*this, std::move(SwordTriangles));
	SwordRenderComponent->SetRenderActive(false);
}
