#include "World.h"
#include "../System/WorldSubsystem/AISystem.h"
#include "../Entity/Obstacle.h"


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

void World::FixedUpdate(float FixedDeltaTime)
{
	for (auto& InstancedActor : InstancedActors)
	{
		InstancedActor->FixedUpdate(FixedDeltaTime);
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


Obstacle* World::SpawnObstacle(const Transform& SpawnTransform, const Vector2 RectDimensions, const SDL_FColor& InColor)
{

	std::unique_ptr<Obstacle> NewActor = std::make_unique<Obstacle>(this, SpawnTransform, RectDimensions, InColor);
	Obstacle* NewActorRaw = NewActor.get();
	InstancedActors.push_back(std::move(NewActor));
	AddActorToMap(NewActorRaw);

	return NewActorRaw;
}