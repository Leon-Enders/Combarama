#include "Obstacle.h"
#include "../Utility/PrimitiveHelpers.h"




Obstacle::Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& InRectDimensions,const SDL_FColor& InColor)
	:
	Actor(GameWorld, InTransform)
{
	BoxCollider = std::make_shared<Collider>(this, InRectDimensions.X, InRectDimensions.Y);


	std::vector<SDL_Vertex> ObstacleTriangles;

	Rectangle ARect = Rectangle(InRectDimensions.X, InRectDimensions.Y);
	ARect.GetVerts(ObstacleTriangles);

	ObstacleRenderComponent = std::make_unique<RenderComponent>(*this, std::move(ObstacleTriangles));
	ObstacleRenderComponent->SetColor(InColor);
}

void Obstacle::Initialize()
{
	BoxCollider->Initialize();
}
