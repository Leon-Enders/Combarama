#pragma once
#include <vector>
#include <memory>
#include <ranges>
#include "../Entity/Actor.h"
#include "../Controller/Controller.h"
#include "../Math/Transform.h"
#include "../System/WorldSubsystem/WorldSubsystem.h"

template<typename T>
concept IsActor = std::is_base_of<Actor, T>::value;

template<typename T>
concept IsController = std::is_base_of<Controller, T>::value;

template<typename T>
concept IsSubsystem = std::is_base_of<WorldSubsystem, T>::value;

class World
{
public:
	void Initialize();
	
	void Update(float DeltaTime);
	
	template<IsActor T>
	T* SpawnActor();

	template<IsActor T>
	T* SpawnActor(const Transform& SpawnTransform);

	template<IsController T>
	T* CreateController();


	template<IsSubsystem T>
	T* GetSubsystem();

	//TODO: Every Actor should have a destroy function calling this Function
	void RemoveActor(Actor* ActorToRemove);



private:
	void FillSubsystemCollection();



	std::vector<std::unique_ptr<WorldSubsystem>> SubsystemCollection;
	std::vector<std::unique_ptr<Actor>> InstancedActors;
	std::vector<std::unique_ptr<Controller>> InstancedControllers;
};



template<IsActor T>
inline T* World::SpawnActor()
{
    static_assert(std::is_base_of<Actor, T>::value,
        "T must be a class derived from Actor");
  
    std::unique_ptr<T> NewActor = std::make_unique<T>(this);

    T* NewActorRaw = NewActor.get();

	InstancedActors.push_back(std::move(NewActor));

    return NewActorRaw;
}

template<IsActor T>
inline T* World::SpawnActor(const Transform& SpawnTransform)
{
	std::unique_ptr<T> NewActor = std::make_unique<T>(this, SpawnTransform);

	T* NewActorRaw = NewActor.get();

	InstancedActors.push_back(std::move(NewActor));

	return NewActorRaw;
}

template<IsController T>
inline T* World::CreateController()
{
	std::unique_ptr<T> NewController = std::make_unique<T>();

	T* NewControllerRaw = NewController.get();

	InstancedControllers.push_back(std::move(NewController));

	return NewControllerRaw;
}

template<IsSubsystem T>
inline T* World::GetSubsystem()
{
	static_assert(std::is_base_of<WorldSubsystem, T>::value,
		"T must be a class derived from Controller");


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
