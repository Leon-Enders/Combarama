#pragma once
#include <vector>
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"
#include "SDL3/SDL_render.h"

struct BodyInstance
{
	BodyInstance(CollisionShape Shape = {}, ECollisionResponseType CollisionResponse = ECollisionResponseType::ECR_None);
	void SetCollisionResponse(const ECollisionResponseType NewCollisionResponse) { CollisionResponse = NewCollisionResponse; }

	CollisionShape Shape;
	std::vector<SDL_Vertex> DebugShape;
	ECollisionResponseType CollisionResponse;
};