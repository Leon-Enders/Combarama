#pragma once
#include <vector>
#include <memory>
#include "../Entity/Actor.h"
#include "../Controller/Controller.h"
#include "../Math/Transform.h"


class World
{
public:

	World();

	template<typename T>
	T* SpawnActor();

	template<typename T>
	T* SpawnActor(const Transform& SpawnTransform);

	template<typename T>
	T* CreateController();


	void Initialize();
	
	void Update(float DeltaTime);


	//TODO: Every Actor should have a destroy function calling this Function
	void RemoveActor(Actor* ActorToRemove);



private:

	std::vector<std::unique_ptr<Actor>> InstancedActors;
	std::vector <std::unique_ptr<Controller>> InstancedControllers;
};

template<typename T>
inline T* World::SpawnActor()
{
    static_assert(std::is_base_of<Actor, T>::value,
        "T must be a class derived from Actor");
  
    std::unique_ptr<T> NewActor = std::make_unique<T>(this);

    T* NewActorRaw = NewActor.get();

	InstancedActors.push_back(std::move(NewActor));

    return NewActorRaw;
}

template<typename T>
inline T* World::SpawnActor(const Transform& SpawnTransform)
{
	static_assert(std::is_base_of<Actor, T>::value,
		"T must be a class derived from Actor");

	std::unique_ptr<T> NewActor = std::make_unique<T>(this, SpawnTransform);

	T* NewActorRaw = NewActor.get();

	InstancedActors.push_back(std::move(NewActor));

	return NewActorRaw;
}

template<typename T>
inline T* World::CreateController()
{
	static_assert(std::is_base_of<Controller, T>::value,
		"T must be a class derived from Controller");

	std::unique_ptr<T> NewController = std::make_unique<T>();

	T* NewControllerRaw = NewController.get();

	InstancedControllers.push_back(std::move(NewController));

	return NewControllerRaw;
}
