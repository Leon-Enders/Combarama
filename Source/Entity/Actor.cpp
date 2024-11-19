#include "Actor.h"
#include "../World/World.h"

Actor::Actor(World* GameWorld, const Transform& InTransform)
	:
	GameObject(GameWorld),
	EntityTransform(InTransform),
	OwningWorld(GameWorld)
{
}


void Actor::Initialize()
{

}

void Actor::Update(float DeltaTime)
{
	for (const auto& Component : ActorComponents)
	{
		Component->Update(DeltaTime);
	}
}

void Actor::FixedUpdate(float FixedDeltaTime)
{
	for (const auto& Component : ActorComponents)
	{
		Component->FixedUpdate(FixedDeltaTime);
	}
}

void Actor::LateUpdate(float DeltaTime)
{
	for (const auto& Component : ActorComponents)
	{
		Component->LateUpdate(DeltaTime);
	}
}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

