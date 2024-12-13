#include "Weapon.h"
#include "../../../RenderCore/Misc/Sword.h"
#include "../../../RenderCore/Misc/ColorHelper.h"
#include "../Component/PrimitiveComponent.h"

Weapon::Weapon(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld, InTransform)
{
	std::vector<SDL_Vertex> SwordTriangles;
	Sword::GenerateVertices(SwordTriangles);


	WeaponPrimitive = CreateComponent<PrimitiveComponent>(std::move(SwordTriangles));
	WeaponPrimitive->SetTransform(LocalTransform);
	WeaponPrimitive->SetColor(COLOR_GREY);
	WeaponPrimitive->SetRenderActive(false);
}

PrimitiveComponent* Weapon::GetWeaponPrimitive()
{
	return WeaponPrimitive;
}
