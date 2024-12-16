#include "Obstacle.h"
#include "../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../Component/PrimitiveComponent.h"


Obstacle::Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions,const SDL_FColor& InColor)
	:
	Actor(GameWorld, InTransform),
	RectDimensions(InRectDimensions),
	ObstacleColour(InColor)
{
	//INFO: Currently you always need to attach a component to the root to update its transform to the gameobjects root
	ObstaclePrimitive = CreateComponent<PrimitiveComponent>(std::move(Rectangle::Make(RectDimensions.X, RectDimensions.Y)));
	ObstaclePrimitive->AttachToComponent(GetRootComponent());
	ObstaclePrimitive->SetColor(ObstacleColour);
}

void Obstacle::Initialize()
{
	BoxCollider = std::make_shared<Collider>(shared_from_this(), RectDimensions.X, RectDimensions.Y);
	BoxCollider->Initialize();
}
