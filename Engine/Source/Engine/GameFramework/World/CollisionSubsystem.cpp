#include "CollisionSubsystem.h"
#include "../Scene/PhysicsScene.h"
#include "../GameObject/Actor.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/CollisionShape.h"

CollisionSubsystem::CollisionSubsystem(World* GameWorld)
	:
	WorldSubsystem(GameWorld)
{
}

void CollisionSubsystem::Initialize()
{
}

bool CollisionSubsystem::SweepByChannel(const PhysicsScene& PScene,
	const Vector2& StartLocation, 
	const Vector2& EndLocation, 
	CollisionResult& OutCollisionResult, 
	const CollisionShape& Shape, 
	ECollisionChannel CollisionChannel, 
	Actor* ActorToIgnore)const
{
	//TODO: Handle CollisionQuery
	// Iterate through the scene and check if the distance of the sweep is less than the distance to a bodyproxy
	// this results in a list of valid targets
	// sweep the shape against each valid target
	// Read how about how you would sweep?


	return false;
}
