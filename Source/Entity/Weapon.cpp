#include "Weapon.h"
#include "../Render/Sword.h"
#include "../Utility/ColorHelper.h"
#include "../Component/PrimitiveComponent.h"

Weapon::Weapon(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	WeaponPrimitive = CreateComponent<PrimitiveComponent>();
}

void Weapon::Initialize()
{
	std::vector<SDL_Vertex> SwordTriangles;
	Sword::GenerateVertices(SwordTriangles, LocalTransform);

	WeaponPrimitive->SetVerts(std::move(SwordTriangles));
	WeaponPrimitive->SetColor(COLOR_GREY);
	WeaponPrimitive->SetRenderActive(false);
}

PrimitiveComponent* Weapon::GetWeaponPrimitive()
{
	return WeaponPrimitive;
}
