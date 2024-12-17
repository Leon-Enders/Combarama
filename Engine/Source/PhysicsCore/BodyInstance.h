#pragma once
#include <vector>
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"
#include "SDL3/SDL_rect.h"

struct BodyInstance
{
	BodyInstance(CollisionShape Shape = {}, ECollisionResponseType CollisionResponse = ECollisionResponseType::ECR_None);
	void SetCollisionResponse(const ECollisionResponseType NewCollisionResponse) { CollisionResponse = NewCollisionResponse; }

	CollisionShape Shape;
	std::vector<SDL_FPoint> DebugShape;
	ECollisionResponseType CollisionResponse;
};