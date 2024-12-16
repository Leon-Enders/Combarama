#include "Sword.h"
#include "../../Core/Math/Matrix.h"

void Sword::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& PivotTransform)
{
	//Matrix3x3 TransformMatrix = Matrix3x3::Transform(PivotTransform);
	TMatrix TransformMatrix = TMatrix::Translate(PivotTransform.Position) *
		TMatrix::Rotate(PivotTransform.Rotation);
		

	for (auto Vert : SwordTriangles)
	{
		Vert.position = TransformMatrix * Vert.position;

		OutVerts.push_back(Vert);
	}
}
