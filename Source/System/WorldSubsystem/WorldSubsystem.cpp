#include "WorldSubsystem.h"
#include "../../World/World.h"

WorldSubsystem WorldSubsystem::Instance;

void WorldSubsystem::Initialize(World* InGameWorld)
{
	GameWorld = InGameWorld;
}

void WorldSubsystem::Update(float DeltaTime)
{
}
