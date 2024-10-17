#include "Sword.h"
#include <vector>


Sword::Sword(const Vector2& InPosition, float Rotation)
{
	std::vector<SDL_Vertex> SwordVerts;
	for (int i = 0; i < 15; i++)
	{
		SwordVerts.push_back(SwordTriangles[i]);
	}
	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordVerts), InPosition, Rotation);
}
