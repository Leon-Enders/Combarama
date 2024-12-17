#include "CollisionSubsystem.h"
#include "../Scene/PhysicsScene.h"

CollisionSubsystem::CollisionSubsystem(World* GameWorld)
	:
	WorldSubsystem(GameWorld)
{
}

void CollisionSubsystem::Initialize()
{
}

bool CollisionSubsystem::SweepByChannel(const PhysicsScene& PScene, const Vector2& StartLocation, CollisionResult& OutCollisionResult, ECollisionChannel CollisionChannel)const
{
	return false;
}
