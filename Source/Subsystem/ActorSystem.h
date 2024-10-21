#pragma once
#include <vector>
#include "../Entity/Actor.h"

class ActorSystem
{
public:
	static ActorSystem& Get() { return Instance; }
	void Initialize();

	void Update(float DeltaTime);

	void AddActor(Actor* ActorToAdd);
	void RemoveActor(Actor* ActorToRemove);

private:
	ActorSystem() = default;
	static ActorSystem Instance;


	std::vector<Actor*> InstancedActors;
};