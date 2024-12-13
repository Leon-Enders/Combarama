#include "World.h"
#include "../System/WorldSubsystem/AISystem.h"
#include "../Entity/Actor.h"
#include "../Entity/Character/Character.h"
#include "../Entity/Character/Enemy.h"
#include "../Entity/Character/PlayerCharacter.h"
#include "../Entity/Weapon.h"
#include "../Entity/Projectile.h"
#include "../Entity/Obstacle.h"
#include "../Entity/Controller/Controller.h"


World::World(Game* theGame)
	:
	theGame(theGame)
{
}

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

	for (auto& InstancedGameObject : InstancedGameObjects)
	{
		if (InstancedGameObject)
		{
			InstancedGameObject->Update(DeltaTime);
		}
	}
}

void World::FixedUpdate(float FixedDeltaTime)
{
	for (auto& InstancedGameObject : InstancedGameObjects)
	{
		if (InstancedGameObject.get())
		{
			InstancedGameObject->FixedUpdate(FixedDeltaTime);
		}
	}
}


void World::LateUpdate(float DeltaTime)
{

	for (auto& InstancedGameObject : InstancedGameObjects)
	{
		if (InstancedGameObject)
		{
			InstancedGameObject->LateUpdate(DeltaTime);
		}
	}
	UpdateInstancedGameObjects();
	CleanUpInstanceGameObjects();
}

void World::DrawDebug()
{
	for (auto& InstancedGameObject : InstancedGameObjects)
	{
		if (InstancedGameObject)
		{
			InstancedGameObject->DrawDebug();
		}
	}
}

void World::UpdateInstancedGameObjects()
{
	if (GameObjectsToAdd.size() <= 0)return;

	for (const auto& GameObjectToAdd : GameObjectsToAdd)
	{
		InstancedGameObjects.push_back(GameObjectToAdd);
	}

	GameObjectsToAdd.clear();
}

void World::CleanUpInstanceGameObjects()
{
	if (GameObjectsToRemove.size() <= 0) return;

	for (const auto GameObjectToRemove : GameObjectsToRemove)
	{
		std::erase_if(InstancedGameObjects, [&](std::shared_ptr<GameObject> InstancedGameObjectPtr)
			{
				return InstancedGameObjectPtr.get() == GameObjectToRemove;
			});
	}


	GameObjectsToRemove.clear();
}

void World::RemoveGameObject(GameObject* GameObjectToRemove)
{
	GameObjectsToRemove.push_back(GameObjectToRemove);
}

void World::FillSubsystemCollection()
{
	SubsystemCollection.emplace_back(std::make_unique<AISystem>(this));
}