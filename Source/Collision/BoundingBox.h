#pragma once
#include <vector>
#include "../Math/Transform.h"




class BoundingBox
{

public:
	BoundingBox(const Vector2 InOrigin, float InBoxHalfWidth, float InBoxHalfHeight);
	void Update(const Transform& NewTransform);

	bool IsCollidingWith(const BoundingBox& Other, float& overlapX, float& overlapY) const;
	void ProjectOntoAxis(const std::vector<Vector2>& corners, const Vector2& axis, float& min, float& max) const;

	inline const std::vector<Vector2>& GetBoundingBoxPoints()const { return BoundingBoxPoints; }

private:

	Vector2 Origin;
	std::vector<Vector2> BoundingBoxPoints;
	std::vector<Vector2> BoundingBoxPointsLocal;
	float BoxHalfWidth;
	float BoxHalfHeight;
};