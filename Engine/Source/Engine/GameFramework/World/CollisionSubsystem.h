#pragma once
#include "WorldSubsystem.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/Misc/CollisionHelper.h"

class PhysicsScene;
class Actor;
struct CollisionShape;

class CollisionSubsystem : public WorldSubsystem
{
public:
	CollisionSubsystem(World* GameWorld);
	virtual void Initialize();

	bool SweepByChannel(const PhysicsScene& PScene,const Vector2& StartLocation, const Vector2& EndLocation, CollisionResult& OutCollisionResult, const CollisionShape& Shape, ECollisionChannel CollisionChannel, Actor* ActorToIgnore)const;
};