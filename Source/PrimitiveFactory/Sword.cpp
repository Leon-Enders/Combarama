#include "Sword.h"
#include "../Math/Matrix.h"

void Sword::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& LocalTransform)
{
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(LocalTransform);
	for (auto Vert : SwordTriangles)
	{
		Vert.position = TransformMatrix * Vert.position;

		OutVerts.push_back(Vert);
	}
}
