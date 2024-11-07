#include "Actor.h"
#include "../World/World.h"


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

void Actor::Destroy()
{
	//TODO: Update with new delegate class
	if (OnDestroyDelegate)
	{
		OnDestroyDelegate();
	}

	GetWorld()->RemoveActor(this);
}

void Actor::DrawDebug()
{

}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

