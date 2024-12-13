#include "GameObject.h"
#include "../World/World.h"
#include "../Coroutine/Awaitable/WaitSeconds.h"

GameObject::GameObject(World* GameWorld)
	:
	OwningWorld(GameWorld)
{
}

void GameObject::Initialize()
{
}

void GameObject::Update(float DeltaTime)
{
}

void GameObject::FixedUpdate(float FixedDeltaTime)
{
}

void GameObject::LateUpdate(float DeltaTime)
{
	// Update all WaitSeconds Awaitables
	for (auto Awaitable : AwaitableContainer)
	{
		Awaitable.get().Update();
	}
}

void GameObject::Destroy()
{
	OnDestroyDelegate.Broadcast();
	GetWorld()->RemoveGameObject(this);
}

void GameObject::DrawDebug()
{
}

void GameObject::AddAwaitable(WaitSeconds& AwaitableToAdd)
{
	AwaitableContainer.push_back(std::ref(AwaitableToAdd));
}

void GameObject::RemoveAwaitable(WaitSeconds& AwaitableToRemove)
{
	std::erase_if(AwaitableContainer, [&](std::reference_wrapper<WaitSeconds> Awaitable)
		{
			return &Awaitable.get() == &AwaitableToRemove;
		});
}
