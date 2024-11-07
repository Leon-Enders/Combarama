#include "Weapon.h"
#include "../Render/Sword.h"
#include "../Utility/ColorHelper.h"

Weapon::Weapon(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;

	Sword::GenerateVertices(SwordTriangles, LocalTransform);

	SwordRenderComponent = std::make_unique<RenderComponent>(*this, std::move(SwordTriangles));
	SwordRenderComponent->SetColor(COLOR_GREY);
	SwordRenderComponent->SetRenderActive(false);
}
