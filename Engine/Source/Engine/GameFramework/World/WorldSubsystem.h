#pragma once
#include <memory>
#include <vector>

class World;

class WorldSubsystem
{
public:
	WorldSubsystem(World* GameWorld);
	virtual void Initialize();
	virtual void Update(float DeltaTime);

protected:
	inline World* GetWorld() { return GameWorld; }

private:

	World* GameWorld = nullptr;
};