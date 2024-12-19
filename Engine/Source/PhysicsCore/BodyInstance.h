#pragma once
#include <vector>
#include <unordered_map>
#include "CollisionShape.h"
#include "Misc/CollisionHelper.h"
#include "SDL3/SDL_rect.h"

class PrimitiveComponent;
class BodyInstance
{
public:
	BodyInstance(PrimitiveComponent* Owner,CollisionShape Shape = {});
	void SetCollisionResponseForChannel(ECollisionChannel CollisionChannel, ECollisionResponseType NewCollisionResponse);
	void SetCollisionShape(const CollisionShape& ShapeToSet);

	const ECollisionResponseType& GetCollisionResponseForChannel(const ECollisionChannel& CollisionChannel)const;
	const std::vector<SDL_FPoint>& GetDebugShape()const;
	const CollisionShape& GetCollisionShape()const;
	const PrimitiveComponent* GetOwningPrimitiveComponent()const;

private:
	PrimitiveComponent* Owner;
	CollisionShape Shape;
	std::vector<SDL_FPoint> DebugShape;
	std::unordered_map<ECollisionChannel, ECollisionResponseType> ResponseForChannel;
};