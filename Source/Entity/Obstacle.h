#pragma once
#include <memory>
#include "SDL3/SDL_rect.h"
#include "Actor.h"
#include "../Collision/Collider.h"
#include "../Render/RenderComponent.h"


class World;

class Obstacle : public Actor
{
public:
	Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions, const SDL_FColor& InColor);

private:
	

	std::unique_ptr<Collider> BoxCollider;
	std::unique_ptr<RenderComponent> ObstacleRenderComponent;
};