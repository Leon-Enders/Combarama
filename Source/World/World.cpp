#include "World.h"

World::World()
{

}

void World::Initialize()
{

}

void World::Update(float DeltaTime)
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->Update(DeltaTime);
	}
}

void World::RemoveActor(Actor* ActorToRemove)
{
	//auto Iterator = std::find(InstancedActors.begin(), InstancedActors.end(), ActorToRemove);
	//
	//if (Iterator != InstancedActors.end())
	//{
	//	InstancedActors.erase(Iterator);
	//}
}
