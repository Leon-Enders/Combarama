#include "Sword.h"

void Sword::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& LocalTransform)
{
	for (int i = 0; i < 15; i++)
	{
		SDL_Vertex NewVert;
		NewVert.position.x = SwordTriangles[i].position.x + LocalTransform.Position.X;
		NewVert.position.y = SwordTriangles[i].position.y + LocalTransform.Position.Y;

		OutVerts.push_back(NewVert);
	}
}
