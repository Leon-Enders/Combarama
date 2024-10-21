#include "ActorSystem.h"

ActorSystem ActorSystem::Instance;

void ActorSystem::Initialize()
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->Initialize();
	}
}

void ActorSystem::Update(float DeltaTime)
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->Update(DeltaTime);
	}
}

void ActorSystem::AddActor(Actor* ActorToAdd)
{
	if (ActorToAdd)
	{
		InstancedActors.push_back(ActorToAdd);
	}
}

void ActorSystem::RemoveActor(Actor* ActorToRemove)
{
	auto Iterator = std::find(InstancedActors.begin(), InstancedActors.end(), ActorToRemove);

	if (Iterator != InstancedActors.end())
	{
		InstancedActors.erase(Iterator);
	}
}
