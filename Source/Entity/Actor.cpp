#include "Actor.h"
#include "../World/World.h"
#include "../Coroutine/Awaitable/WaitSeconds.h"

Actor::Actor(World* GameWorld, const Transform& InTransform)
	:
	EntityTransform(InTransform),
	OwningWorld(GameWorld)
{
}

void Actor::Initialize()
{

}




void Actor::Update(float DeltaTime)
{
	
}

void Actor::FixedUpdate(float FixedDeltaTime)
{

}


void Actor::LateUpdate(float DeltaTime)
{
	// Update all WaitSeconds Awaitables
	for (auto Awaitable : AwaitableContainer)
	{
		Awaitable.get().Update();
	}
}

void Actor::Destroy()
{
	OnDestroyDelegate.Broadcast();
	GetWorld()->RemoveActor(this);
}

void Actor::DrawDebug()
{

}


void Actor::AddAwaitable(WaitSeconds& AwaitablePtrToAdd)
{
	AwaitableContainer.push_back(std::ref(AwaitablePtrToAdd));
}

void Actor::RemoveAwaitable(WaitSeconds& AwaitableToRemove)
{
	std::erase_if(AwaitableContainer, [&](std::reference_wrapper<WaitSeconds> Awaitable)
		{
			return &Awaitable.get() == &AwaitableToRemove;
		});
}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

