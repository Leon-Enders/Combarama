#include "Sword.h"
#include <vector>


Sword::Sword(const Transform& InTransform, const Vector2& SwordOffset)
{
	//Generate Triangles for Sword
	std::vector<SDL_Vertex> SwordVerts;
	for (int i = 0; i < 15; i++)
	{
		SDL_Vertex NewVert;
		NewVert.position.x = SwordTriangles[i].position.x + InTransform.Position.X;
		NewVert.position.y = SwordTriangles[i].position.y + InTransform.Position.Y;

		SwordVerts.push_back(NewVert);
	}

	// Offset Origin Sword Transform
	Transform SwordTransform = InTransform;
	SwordTransform.Position += SwordOffset;

	//Move Triangles for Sword to RenderComponent
	SwordRenderComponent = std::make_unique<RenderComponent>(std::move(SwordVerts), SwordTransform);
}
