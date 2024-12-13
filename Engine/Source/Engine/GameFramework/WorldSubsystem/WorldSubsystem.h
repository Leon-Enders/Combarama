#pragma once

class World;

class WorldSubsystem
{
public:
	WorldSubsystem(World* InGameWorld);
	virtual void Initialize();
	virtual void Update(float DeltaTime);

protected:
	inline World* GetWorld() { return GameWorld; }

private:

	World* GameWorld = nullptr;
};