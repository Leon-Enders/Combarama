#include "World.h"
#include "../System/WorldSubsystem/AISystem.h"


void World::Initialize()
{
	// Add all WorldSubsystems and Initialize them
	FillSubsystemCollection();

	for (const auto& ActiveSubsystem : SubsystemCollection)
	{
		ActiveSubsystem->Initialize();
	}
}

void World::Update(float DeltaTime)
{
	for (auto& Subsystem : SubsystemCollection)
	{
		Subsystem->Update(DeltaTime);
	}


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

void World::FillSubsystemCollection()
{
	SubsystemCollection.emplace_back(std::make_unique<AISystem>(this));
}
