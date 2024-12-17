#pragma once
#include "WorldSubsystem.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/Misc/CollisionHelper.h"

class PhysicsScene;

class CollisionSubsystem : public WorldSubsystem
{
public:
	CollisionSubsystem(World* GameWorld);
	virtual void Initialize();

	bool SweepByChannel(const PhysicsScene& PScene,const Vector2& StartLocation, CollisionResult& OutCollisionResult, ECollisionChannel CollisionChannel)const;
};