#include "Sword.h"
#include "../Math/Transform.h"

void Sword::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& OriginTransform)
{
	for (int i = 0; i < 15; i++)
	{
		SDL_Vertex NewVert;
		NewVert.position.x = SwordTriangles[i].position.x + OriginTransform.Position.X;
		NewVert.position.y = SwordTriangles[i].position.y + OriginTransform.Position.Y;

		OutVerts.push_back(NewVert);
	}
}
