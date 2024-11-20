#include "WeaponComponent.h"
#include "../PrimitiveFactory/Sword.h"
#include "../Utility/ColorHelper.h"


void WeaponComponent::Initialize(Actor* Owner)
{
	PrimitiveComponent::Initialize(Owner);

	std::vector<SDL_Vertex> SwordTriangles;
	Sword::GenerateVertices(SwordTriangles);

	SetVerts(std::move(SwordTriangles));
	SetColor(COLOR_GREY);
	SetRenderActive(false);
}
