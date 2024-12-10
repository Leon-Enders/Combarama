#pragma once
#include "../Event/Delegate.h"



class World;
class WaitSeconds;

class GameObject
{
public:
	GameObject(World* GameWorld);
	virtual ~GameObject() = default;
	GameObject(const GameObject& Other) = delete;
	GameObject(GameObject&& Other) = delete;
	GameObject& operator=(const GameObject& Other) = delete;
	GameObject& operator=(GameObject&& Other) = delete;

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Destroy();

	virtual void DrawDebug();

	inline World* GetWorld() const { return OwningWorld; }


	void AddAwaitable(WaitSeconds& AwaitableToAdd);
	void RemoveAwaitable(WaitSeconds& AwaitableToRemove);

public:
	MulticastDelegate<void, void> OnDestroyDelegate;

private:
	World* OwningWorld = nullptr;


	std::vector <std::reference_wrapper<WaitSeconds>> AwaitableContainer;
};