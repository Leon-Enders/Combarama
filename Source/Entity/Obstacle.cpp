#include "Obstacle.h"
#include "../Utility/PrimitiveHelpers.h"
#include "../Component/PrimitiveComponent.h"


Obstacle::Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions,const SDL_FColor& InColor)
	:
	Actor(GameWorld, InTransform),
	RectDimensions(InRectDimensions),
	ObstacleColour(InColor)
{
	
	ObstaclePrimitive = CreateComponent<PrimitiveComponent>();
}

void Obstacle::Initialize()
{
	std::vector<SDL_Vertex> ObstacleTriangles;

	Rectangle ARect = Rectangle(RectDimensions.X, RectDimensions.Y);
	ARect.GetVerts(ObstacleTriangles);

	ObstaclePrimitive->SetVerts(std::move(ObstacleTriangles));
	ObstaclePrimitive->SetColor(ObstacleColour);

	BoxCollider = std::make_shared<Collider>(shared_from_this(), RectDimensions.X, RectDimensions.Y);
	BoxCollider->Initialize();
}
