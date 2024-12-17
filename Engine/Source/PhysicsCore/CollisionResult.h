#pragma once
#include "../Core/Math/Vector2.h"

class CollisionResult
{
public:
	Vector2 Position;
	Vector2 ImpactPoint;
	bool bBlockingHit;
};