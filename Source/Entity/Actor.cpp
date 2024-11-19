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

const Vector2& Actor::GetPosition() const
{
	return RootComponent->GetPosition();
}

const float Actor::GetRotation() const
{
	return RootComponent->GetRotation();
}

const Vector2& Actor::GetScale() const
{
	return RootComponent->GetScale();
}

const Vector2 Actor::GetForwardVector() const
{
	return GetTransform().GetForwardVector();
}


void Actor::SetTransform(const Transform& InTransform)
{
	RootComponent->SetTransform(InTransform);
}

void Actor::SetPosition(const Vector2& InPosition)
{
	RootComponent->SetPosition(InPosition);
}

void Actor::SetRotation(float InRotation)
{
	RootComponent->SetRotation(InRotation);
}

void Actor::SetScale(const Vector2& InScale)
{
	RootComponent->SetScale(InScale);
}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

