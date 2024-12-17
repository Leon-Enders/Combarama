#pragma once
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"

class BodyInstance
{
public:
	BodyInstance(CollisionShape Shape ={}, ECollisionResponseType CollisionResponse = ECollisionResponseType::ECR_None)
	:
		Shape(Shape),
		CollisionResponse(CollisionResponse)
	{
	}

	void SetCollisionResponse(const ECollisionResponseType NewCollisionResponse) { CollisionResponse = NewCollisionResponse; }

private:
	CollisionShape Shape;
	ECollisionResponseType CollisionResponse;
};