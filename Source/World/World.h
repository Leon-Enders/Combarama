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
	std::vector<std::shared_ptr<Actor>>,
	std::vector<std::shared_ptr<Character>>,
	std::vector<std::shared_ptr<Enemy>>,
	std::vector<std::shared_ptr<PlayerCharacter>>,
	std::vector<std::shared_ptr<Weapon>>,
	std::vector<std::shared_ptr<Obstacle>>,
	std::vector<std::shared_ptr<Projectile>>>;


class World
{
public:
	void Initialize();
	
	void Update(float DeltaTime);
	void FixedUpdate(float FixedDeltaTime);
	void DrawDebug();

	template<IsActor T>
	T* SpawnActor();

	template<IsActor T>
	T* SpawnActor(const Transform& SpawnTransform);

	Obstacle* SpawnObstacle(const Transform& SpawnTransform, const Vector2 RectDimensions, const SDL_FColor& InColor);

	template<IsActor T>
	std::vector<std::shared_ptr<T>>& GetAllActorsOfClass();

	template<IsController T>
	T* CreateController();

	template<IsSubsystem T>
	T* GetSubsystem();


	void RemoveActor(Actor* ActorToRemove);
	void RemoveController(Controller* ControllerToRemove);

private:
	template<IsActor T>
	void AddActorToMap(T* ActorToAdd);

	void FillSubsystemCollection();


private:

	std::unordered_map<std::type_index, ActorsVariant> ActorTypeToActorsMap;
	std::vector<std::unique_ptr<WorldSubsystem>> SubsystemCollection;
	std::vector<std::shared_ptr<Actor>> InstancedActors;
	std::vector<std::shared_ptr<Controller>> InstancedControllers;
};



template<IsActor T>
inline T* World::SpawnActor()
{
	std::shared_ptr<T> NewActor = std::make_shared<T>(this);
	T* NewActorRaw = NewActor.get();
	InstancedActors.push_back(std::move(NewActor));
	AddActorToMap(NewActorRaw);

	return NewActorRaw;
}

template<IsActor T>
inline T* World::SpawnActor(const Transform& SpawnTransform)
{
	std::shared_ptr<T> NewActor = std::make_shared<T>(this, SpawnTransform);
	T* NewActorRaw = NewActor.get();
	InstancedActors.push_back(std::move(NewActor));
	AddActorToMap(NewActorRaw);

	return NewActorRaw;
}

template<IsActor T>
inline std::vector<std::shared_ptr<T>>& World::GetAllActorsOfClass()
{
	std::type_index TypeIndex = std::type_index(typeid(T));
	auto it = ActorTypeToActorsMap.find(TypeIndex);

	if (it != ActorTypeToActorsMap.end()) {
		return std::get<std::vector<std::shared_ptr<T>>>(it->second);
	}

	
	std::vector<std::shared_ptr<T>> EmptyVector;
	return EmptyVector;
}

template<IsActor T>
inline void World::AddActorToMap(T* ActorToAdd)
{
	std::type_index TypeIndex = std::type_index(typeid(T));

	auto it = ActorTypeToActorsMap.find(TypeIndex);
	if (it == ActorTypeToActorsMap.end()) 
	{
		std::vector<std::shared_ptr<T>> NewVector;
		ActorTypeToActorsMap[TypeIndex] = NewVector;
		it = ActorTypeToActorsMap.find(TypeIndex);
	}

	auto& ActorVector = std::get<std::vector<std::shared_ptr<T>>>(it->second);
	ActorVector.emplace_back(ActorToAdd);
}



template<IsController T>
inline T* World::CreateController()
{
	std::shared_ptr<T> NewController = std::make_shared<T>(this);

	T* NewControllerRaw = NewController.get();

	InstancedControllers.push_back(std::move(NewController));

	return NewControllerRaw;
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




