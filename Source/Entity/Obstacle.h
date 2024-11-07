#pragma once
#include <memory>
#include "SDL3/SDL_rect.h"
#include "Actor.h"
#include "../Collision/Collider.h"
#include "../Render/RenderComponent.h"


class World;

class Obstacle : public Actor, public std::enable_shared_from_this<Obstacle>
{
public:
	Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions, const SDL_FColor& InColor);

	virtual void Initialize() override;

private:
	
	Vector2 RectDimensions;

	std::shared_ptr<Collider> BoxCollider;
	std::unique_ptr<RenderComponent> ObstacleRenderComponent;
};