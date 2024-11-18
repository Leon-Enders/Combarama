#pragma once
#include "../Event/Delegate.h"


class World;

class GameObject
{
public:
	GameObject(World* GameWorld);
	virtual ~GameObject() = default;

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Destroy();


protected:
	inline World* GetWorld()const { return OwningWorld; }

public:
	MulticastDelegate<void, void> OnDestroyDelegate;

private:
	World* OwningWorld = nullptr;
};