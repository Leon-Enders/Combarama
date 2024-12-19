#pragma once
#include <vector>
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"
#include "SDL3/SDL_rect.h"

class PrimitiveComponent;
class BodyInstance
{
public:
	BodyInstance(PrimitiveComponent* Owner,CollisionShape Shape = {}, ECollisionResponseType CollisionResponse = ECollisionResponseType::ECR_None, ECollisionChannel CollisionChannel = ECollisionChannel::ECC_None);
	void SetCollisionResponse(const ECollisionResponseType NewCollisionResponse) { CollisionResponse = NewCollisionResponse; }
	void SetCollisionShape(const CollisionShape& ShapeToSet);

	const ECollisionResponseType GetCollisionResponseType()const { return CollisionResponse; }
	const ECollisionChannel GetCollisionChannel()const { return CollisionChannel; }
	const std::vector<SDL_FPoint>& GetDebugShape()const;
	const CollisionShape& GetCollisionShape()const;
	const PrimitiveComponent* GetOwningPrimitiveComponent()const;

private:
	PrimitiveComponent* Owner;
	CollisionShape Shape;
	std::vector<SDL_FPoint> DebugShape;
	ECollisionResponseType CollisionResponse;
	ECollisionChannel CollisionChannel;
};