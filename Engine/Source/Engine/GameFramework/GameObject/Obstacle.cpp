#include "Obstacle.h"
#include "../../../RenderCore/Misc/PrimitiveHelpers.h"
#include "../Component/PrimitiveComponent.h"


Obstacle::Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions,const SDL_FColor& InColor)
	:
	Actor(GameWorld, InTransform),
	RectDimensions(InRectDimensions),
	ObstacleColour(InColor)
{
	std::vector<SDL_Vertex> ObstacleTriangles;

	Rectangle ARect = Rectangle(RectDimensions.X, RectDimensions.Y);
	ARect.GetVerts(ObstacleTriangles);

	ObstaclePrimitive = CreateComponent<PrimitiveComponent>(std::move(ObstacleTriangles));
	ObstaclePrimitive->SetColor(ObstacleColour);
}

void Obstacle::Initialize()
{
	BoxCollider = std::make_shared<Collider>(shared_from_this(), RectDimensions.X, RectDimensions.Y);
	BoxCollider->Initialize();
}
