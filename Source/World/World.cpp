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



void World::LateUpdate(float DeltaTime)
{



	for (auto& InstancedActor : InstancedActors)
	{
		if (InstancedActor)
		{
			InstancedActor->LateUpdate(DeltaTime);
		}
	}
	UpdateInstancedActors();
	CleanUpInstanceActors();
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
		if (InstancedActor.get())
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

void World::UpdateInstancedActors()
{
	if (ActorsToAdd.size() <= 0)return;

	for (const auto& ActorToAdd : ActorsToAdd)
	{
		InstancedActors.push_back(ActorToAdd);
	}

	ActorsToAdd.clear();
}

void World::CleanUpInstanceActors()
{
	if (ActorsToRemove.size() <= 0) return;

	for (const auto ActorToRemove : ActorsToRemove)
	{
		std::erase_if(InstancedActors, [&](std::shared_ptr<Actor> InstancedActorPtr)
			{
				return InstancedActorPtr.get() == ActorToRemove;
			});
	}


	ActorsToRemove.clear();
}

void World::RemoveActor(Actor* ActorToRemove)
{
	ActorsToRemove.push_back(ActorToRemove);
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


std::weak_ptr<Obstacle> World::SpawnObstacle(const Transform& SpawnTransform, const Vector2 RectDimensions, const SDL_FColor& InColor)
{

	std::shared_ptr<Obstacle> NewActor = std::make_shared<Obstacle>(this, SpawnTransform, RectDimensions, InColor);
	std::weak_ptr<Obstacle> wNewActor = NewActor;

	NewActor->Initialize();


	AddActorToMap(NewActor);
	InstancedActors.push_back(std::move(NewActor));


	return wNewActor;
}