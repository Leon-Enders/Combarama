#include "BoundingBox.h"
#include "../Math/Matrix.h"

BoundingBox::BoundingBox(const Vector2 InOrigin, float InBoxHalfWidth, float InBoxHalfHeight)
	:
	Origin(InOrigin),
	BoxHalfWidth(InBoxHalfWidth),
	BoxHalfHeight(InBoxHalfHeight)
{
	BoundingBoxPoints.resize(4);
	BoundingBoxPointsLocal.resize(4);

	//Minpoint = Vector2(Origin.X - BoxHalfWidth, Origin.Y - BoxHalfHeight);
	//Maxpoint = Vector2(Origin.X + BoxHalfWidth, Origin.Y + BoxHalfHeight);

	BoundingBoxPoints[0].X = - BoxHalfWidth;  // Top-left corner
	BoundingBoxPoints[0].Y = - BoxHalfHeight;

	BoundingBoxPoints[1].X = + BoxHalfWidth;  // Top-right corner
	BoundingBoxPoints[1].Y = - BoxHalfHeight;

	BoundingBoxPoints[2].X = + BoxHalfWidth;  // Bottom-right corner
	BoundingBoxPoints[2].Y = + BoxHalfHeight;

	BoundingBoxPoints[3].X = - BoxHalfWidth;  // Bottom-left corner
	BoundingBoxPoints[3].Y = + BoxHalfHeight;

	BoundingBoxPointsLocal = BoundingBoxPoints;
}

void BoundingBox::Update(const Transform& NewTransform)
{
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(NewTransform);

	for (int i = 0; i < 4; i++)
	{
		BoundingBoxPoints[i] = TransformMatrix.MultiplyVector2(BoundingBoxPointsLocal[i]);
	}
}
