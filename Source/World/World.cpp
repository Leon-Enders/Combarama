#include "World.h"

World::World()
{

}

void World::Initialize()
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->Initialize();
	}
}

void World::Update(float DeltaTime)
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->Update(DeltaTime);
	}
}
