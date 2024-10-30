#include "Actor.h"
#include "../World/World.h"


Actor::Actor(World* GameWorld)
	:
	OwningWorld(GameWorld)
{
}

Actor::Actor(World* GameWorld, const Transform& InTransform)
	:
	EntityTransform(InTransform),
	OwningWorld(GameWorld)
{
	Initialize();
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

void Actor::Destroy()
{
	if (OnDestroyDelegate)
	{
		OnDestroyDelegate();
	}

	GetWorld()->RemoveActor(this);
}

void Actor::DrawDebug()
{
}
