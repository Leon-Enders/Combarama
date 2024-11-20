#include "WeaponComponent.h"
#include "../PrimitiveFactory/Sword.h"
#include "../Utility/ColorHelper.h"


void WeaponComponent::Initialize(Actor* Owner)
{
	PrimitiveComponent::Initialize(Owner);

	//INFO: Setting the transform for the start verts will
	// essentially determine the pivot point of the primitive
	std::vector<SDL_Vertex> SwordTriangles;
	Sword::GenerateVertices(SwordTriangles, {{ 75.f,0.f }, 1.5708f, { 1.f,1.f }});

	SetVerts(std::move(SwordTriangles));
	SetColor(COLOR_GREY);
	SetRenderActive(false);
}
