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
		if (InstancedActor)
		{
			InstancedActor->Update(DeltaTime);
		}
	}

	for (auto& InstancedController : InstancedControllers)
	{
		if (InstancedController)
		{
			InstancedController->Update(DeltaTime);
		}
	}
}

void World::FixedUpdate(float FixedDeltaTime)
{
	for (auto& InstancedActor : InstancedActors)
	{
		if (InstancedActor)
		{
			InstancedActor->FixedUpdate(FixedDeltaTime);
		}
	}
}

void World::DrawDebug()
{
	for (auto& InstancedActor : InstancedActors)
	{
		if (InstancedActor)
		{
			InstancedActor->DrawDebug();
		}
	}
}

void World::RemoveActor(Actor* ActorToRemove)
{
	std::erase_if(InstancedActors, [&](std::shared_ptr<Actor>& InstancedActorPtr)
		{
			return InstancedActorPtr.get() == ActorToRemove;
		});
}

void World::RemoveController(Controller* ControllerToRemove)
{
	std::erase_if(InstancedControllers, [&](std::shared_ptr<Controller>& InstancedControllerPtr)
		{
			return InstancedControllerPtr.get() == ControllerToRemove;
		});
}

void World::FillSubsystemCollection()
{
	SubsystemCollection.emplace_back(std::make_unique<AISystem>(this));
}


Obstacle* World::SpawnObstacle(const Transform& SpawnTransform, const Vector2 RectDimensions, const SDL_FColor& InColor)
{

	std::shared_ptr<Obstacle> NewActor = std::make_shared<Obstacle>(this, SpawnTransform, RectDimensions, InColor);
	Obstacle* ActorRaw = NewActor.get();
	AddActorToMap(NewActor);
	InstancedActors.push_back(std::move(NewActor));


	return ActorRaw;
}