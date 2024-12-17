#pragma once
#include "WorldSubsystem.h"
#include "../../../PhysicsCore/CollisionResult.h"


class CollisionSubsystem : public WorldSubsystem
{
public:
	CollisionSubsystem(World* GameWorld);
	virtual void Initialize();

};