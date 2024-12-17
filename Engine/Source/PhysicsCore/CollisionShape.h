#pragma once
#include "../Core/Math/Vector2.h"

//TODO: Make it real abstract, default shape is circle
struct CollisionShape
{
	CollisionShape(float Radius = 5.f)
		:
		Radius(Radius)
	{}
	float Radius;
};