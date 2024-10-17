#include "Sword.h"
#include <vector>


Sword::Sword(const Vector2& InPosition, float Rotation, const Vector2& SwordOffset)
{
	std::vector<SDL_Vertex> SwordVerts;
	for (int i = 0; i < 15; i++)
	{
		SDL_Vertex NewVert;
		NewVert.position.x = SwordTriangles[i].position.x + InPosition.X;
		NewVert.position.y = SwordTriangles[i].position.y + InPosition.Y;

		SwordVerts.push_back(NewVert);
	}
	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordVerts), InPosition, Rotation, SwordOffset);
}
