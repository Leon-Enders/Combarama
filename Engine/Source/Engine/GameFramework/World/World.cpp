#include "World.h"
#include "AISubsystem.h"
#include "CollisionSubsystem.h"
#include "../GameObject/Actor.h"
#include "../GameObject/Character/Character.h"
#include "../GameObject/Character/Enemy.h"
#include "../GameObject/Character/PlayerCharacter.h"
#include "../GameObject/Projectile.h"
#include "../GameObject/Obstacle.h"
#include "../GameObject/Controller/Controller.h"


World::World(Game* theGame)
	:
	theGame(theGame)
{
}

void World::Initialize()
{
	// Create all WorldSubsystems and Initialize them
	CreateSubsystemCollection();

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

void World::CreateSubsystemCollection()
{
	SubsystemCollection.emplace_back(std::make_unique<AISubsystem>(this));
	SubsystemCollection.emplace_back(std::make_unique<CollisionSubsystem>(this));
}