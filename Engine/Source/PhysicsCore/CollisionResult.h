#pragma once
#include "../Core/Math/Vector2.h"

struct CollisionResult
{
	Vector2 Position;
	Vector2 ImpactPoint;
	bool bBlockingHit = false;
};