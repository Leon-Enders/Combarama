#include "Obstacle.h"
#include "../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../Component/PrimitiveComponent.h"


Obstacle::Obstacle(World* GameWorld, const Transform& InTransform, const Vector2& RectHalfExtent,const SDL_FColor& InColor)
	:
	Actor(GameWorld, InTransform),
	ObstacleColour(InColor)
{
	//INFO: Currently you always need to attach a component to the root to update its transform to the gameobjects root
	ObstaclePrimitive = CreateComponent<PrimitiveComponent>(std::move(RectPrimitive::Make(RectHalfExtent.X, RectHalfExtent.Y)));
	ObstaclePrimitive->AttachToComponent(GetRootComponent());
	ObstaclePrimitive->SetColor(ObstacleColour);
	ObstaclePrimitive->SetCollisionShape(CollisionShape::MakeRect(RectHalfExtent));
	ObstaclePrimitive->SetCollisionResponseForChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponseType::ECR_Block);
	ObstaclePrimitive->SetCollisionResponseForChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponseType::ECR_Block);
	ObstaclePrimitive->SetCollisionResponseForChannel(ECollisionChannel::ECC_Projectile, ECollisionResponseType::ECR_Overlap);
}

void Obstacle::Initialize()
{
	
}
