#pragma once
#include <vector>
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"
#include "SDL3/SDL_rect.h"

class BodyInstance
{
public:
	BodyInstance(CollisionShape Shape = {}, ECollisionResponseType CollisionResponse = ECollisionResponseType::ECR_None);
	void SetCollisionResponse(const ECollisionResponseType NewCollisionResponse) { CollisionResponse = NewCollisionResponse; }
	void SetCollisionShape(const CollisionShape& ShapeToSet);
	const std::vector<SDL_FPoint>& GetDebugShape()const;
	const CollisionShape& GetCollisionShape()const;

private:
	CollisionShape Shape;
	std::vector<SDL_FPoint> DebugShape;
	ECollisionResponseType CollisionResponse;
};