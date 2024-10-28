#pragma once
#include <vector>
#include "../Math/Transform.h"




class BoundingBox
{

public:
	BoundingBox(const Vector2 InOrigin, float InBoxHalfWidth, float InBoxHalfHeight);
	void Update(const Transform& NewTransform);

	inline const std::vector<Vector2>& GetBoundingBoxPoints()const { return BoundingBoxPoints; }

private:

	Vector2 Origin;
	Vector2 Minpoint;
	Vector2 Maxpoint;
	std::vector<Vector2> BoundingBoxPoints;
	std::vector<Vector2> BoundingBoxPointsLocal;
	float BoxHalfWidth;
	float BoxHalfHeight;
};