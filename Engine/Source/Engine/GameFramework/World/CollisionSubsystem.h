#pragma once
#include "WorldSubsystem.h"


class CollisionSubsystem : public WorldSubsystem
{
public:
	CollisionSubsystem(World* GameWorld);
	virtual void Initialize();

};