#pragma once
#include <vector>
#include <memory>
#include <ranges>
#include <unordered_map>
#include <typeindex>
#include <variant>
#include <functional>
#include "../Entity/Actor.h"
#include "../Entity/Character.h"
#include "../Entity/Enemy.h"
#include "../Entity/PlayerCharacter.h"
#include "../Entity/Weapon.h"
#include "../Entity/Projectile.h"
#include "../Controller/Controller.h"
#include "../Math/Transform.h"
#include "../System/WorldSubsystem/WorldSubsystem.h"



class Obstacle;

template<typename T>
concept IsActor = std::is_base_of<Actor, T>::value;

template<typename T>
concept IsController = std::is_base_of<Controller, T>::value;

template<typename T>
concept IsSubsystem = std::is_base_of<WorldSubsystem, T>::value;



using ActorsVariant = std::variant<
	std::vector<std::weak_ptr<Actor>>,
	std::vector<std::weak_ptr<Character>>,
	std::vector<std::weak_ptr<Enemy>>,
	std::vector<std::weak_ptr<PlayerCharacter>>,
	std::vector<std::weak_ptr<Weapon>>,
	std::vector<std::weak_ptr<Obstacle>>,
	std::vector<std::weak_ptr<Projectile>>>;

class World
{
public:
	void Initialize();
	
	void Update(float DeltaTime);
	void FixedUpdate(float FixedDeltaTime);
	void DrawDebug();

	template<IsActor T>
	std::weak_ptr<T> SpawnActor(const Transform& SpawnTransform);

	std::weak_ptr<Obstacle> SpawnObstacle(const Transform& SpawnTransform, const Vector2 RectDimensions, const SDL_FColor& InColor);

	template<IsActor T>
	std::vector<std::shared_ptr<T>> GetAllActorsOfClass();

	template<IsController T>
	std::weak_ptr<T> CreateController();

	template<IsSubsystem T>
	T* GetSubsystem();


	void RemoveActor(Actor* ActorToRemove);
	void RemoveController(Controller* ControllerToRemove);

private:
	template<IsActor T>
	void AddActorToMap(std::shared_ptr<T> ActorToAdd);

	void FillSubsystemCollection();


private:

	std::unordered_map<std::type_index, ActorsVariant> ActorTypeToActorsMap;
	std::vector<std::unique_ptr<WorldSubsystem>> SubsystemCollection;
	std::vector<std::shared_ptr<Actor>> InstancedActors;
	std::vector<std::shared_ptr<Controller>> InstancedControllers;
};

template<IsActor T>
inline std::weak_ptr<T> World::SpawnActor(const Transform& SpawnTransform)
{
	std::shared_ptr<T> NewActor = std::make_shared<T>(this, SpawnTransform);
	std::weak_ptr<T> NewActorWeak = NewActor;

	//Small hack to initialize Actor
	Actor* InitializationPtr = static_cast<Actor*>(NewActor.get());
	InitializationPtr->Initialize();
	
	
	AddActorToMap(NewActor);
	InstancedActors.push_back(std::move(NewActor));
	
	return NewActorWeak;
}

template <IsActor T>
std::vector<std::shared_ptr<T>> World::GetAllActorsOfClass()
{
	std::type_index TypeIndex = std::type_index(typeid(T));
	auto it = ActorTypeToActorsMap.find(TypeIndex);

	if (it != ActorTypeToActorsMap.end()) {
		auto& WeakActorVector = std::get<std::vector<std::weak_ptr<T>>>(it->second);

		std::vector<std::shared_ptr<T>> ValidActors;
		WeakActorVector.erase(std::remove_if(WeakActorVector.begin(), WeakActorVector.end(),
			[&ValidActors](const std::weak_ptr<T>& WeakPtr)
			{
				if (auto SharedPtr = WeakPtr.lock())
				{
					ValidActors.push_back(SharedPtr);
					return false;
				}
				return true; 
			}), WeakActorVector.end());

		return ValidActors;
	}

	return {};
}

template<IsActor T>
inline void World::AddActorToMap(std::shared_ptr<T> ActorToAdd)
{
	std::type_index TypeIndex = std::type_index(typeid(T));

	auto it = ActorTypeToActorsMap.find(TypeIndex);
	if (it == ActorTypeToActorsMap.end()) 
	{
		std::vector<std::weak_ptr<T>> NewVector;
		ActorTypeToActorsMap[TypeIndex] = NewVector;
		it = ActorTypeToActorsMap.find(TypeIndex);
	}

	auto& ActorVector = std::get<std::vector<std::weak_ptr<T>>>(it->second);
	ActorVector.push_back(ActorToAdd);
}



template<IsController T>
inline std::weak_ptr<T> World::CreateController()
{
	std::shared_ptr<T> NewController = std::make_shared<T>(this);

	std::weak_ptr<T> NewControllerWeakPtr = NewController;

	InstancedControllers.push_back(std::move(NewController));

	return NewControllerWeakPtr;
}

template<IsSubsystem T>
inline T* World::GetSubsystem()
{
	auto Iterator = std::ranges::find_if(SubsystemCollection,
		[](const std::unique_ptr<WorldSubsystem>& Subsystem)
		{
			return dynamic_cast<T*>(Subsystem.get()) != nullptr;
		});

	if (Iterator != SubsystemCollection.end()) 
	{
		return dynamic_cast<T*>(Iterator->get());
	}

	return nullptr;
}




