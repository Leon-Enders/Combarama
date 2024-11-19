#include "Actor.h"
#include "../World/World.h"
#include "../Component/SceneComponent.h"

Actor::Actor(World* GameWorld, const Transform& InTransform)
	:
	GameObject(GameWorld),
	EntityTransform(InTransform),
	OwningWorld(GameWorld)
{
	RootComponent = CreateComponent<SceneComponent>();
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


const Transform& Actor::GetTransform() const
{
	return RootComponent->GetTransform();
}

void Actor::SetTransform(const Transform& InTransform)
{
	RootComponent->SetTransform(InTransform);
}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

