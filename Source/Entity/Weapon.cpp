#include "Weapon.h"
#include "../Render/Sword.h"

Weapon::Weapon()
	:
	Actor()
{
}

Weapon::Weapon(const Transform& InTransform)
	:
	Actor(InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, InTransform);

	EntityTransform.Position += WeaponOffset;

	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordTriangles), this);
	SwordRenderComponent->SetRenderActive(false);
}
