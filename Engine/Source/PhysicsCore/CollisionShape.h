#pragma once
#include "../Core/Math/Vector2.h"

//TODO: Make it real abstract, default shape is circle
class CollisionShape
{
public:
	CollisionShape(Vector2 Origin={}, float Radius = 5.f)
		:
		Origin(Origin),
		Radius(Radius)
	{}
private:
	Vector2 Origin;
	float Radius;
};