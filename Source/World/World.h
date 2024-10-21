#pragma once
#include <vector>
#include <memory>
#include "../Entity/Actor.h"


class World
{
public:

	World();

	template<typename T>
	T* SpawnActor();

	void Initialize();
	
	void Update(float DeltaTime);

private:

	std::vector<std::unique_ptr<Actor>> InstancedActors;
};

template<typename T>
inline T* World::SpawnActor()
{
    static_assert(std::is_base_of<Actor, T>::value,
        "T must be a class derived from Actor");
  
    std::unique_ptr<T> NewActor = std::make_unique<T>();

    T* NewActorRaw = NewActor.get();

	InstancedActors.push_back(std::move(NewActor));

    return NewActorRaw;
}
