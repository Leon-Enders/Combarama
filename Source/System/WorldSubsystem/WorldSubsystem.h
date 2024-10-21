#pragma once

class World;

class WorldSubsystem
{
public:

	static WorldSubsystem& Get() { return Instance; }
	virtual void Initialize(World* InGameWorld);
	virtual void Update(float DeltaTime);

protected:
	inline World* GetWorld() { return GameWorld; }

private:
	static WorldSubsystem Instance;

	World* GameWorld = nullptr;
};