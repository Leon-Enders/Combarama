#pragma once
#include <memory>
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_pixels.h"
#include "Actor.h"
#include "../Collision/Collider.h"
#include "../Render/RenderComponent.h"

class PrimitiveComponent;
class World;

class Obstacle : public Actor, public std::enable_shared_from_this<Obstacle>
{
public:
	Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions, const SDL_FColor& InColor);

	virtual void Initialize() override;

private:
	
	Vector2 RectDimensions;

	SDL_FColor ObstacleColour;

	PrimitiveComponent* ObstaclePrimitive = nullptr;
	std::shared_ptr<Collider> BoxCollider;
};