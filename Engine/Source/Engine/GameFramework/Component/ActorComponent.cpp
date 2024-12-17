#include "ActorComponent.h"
#include "../GameObject/Actor.h"

ActorComponent::ActorComponent(Actor* Owner)
	:
	Owner(Owner)
{
}

ActorComponent::~ActorComponent()
{
}

void ActorComponent::Initialize()
{
}

void ActorComponent::Update(float DeltaTime)
{
}

void ActorComponent::FixedUpdate(float FixedDeltaTime)
{
}

void ActorComponent::LateUpdate(float DeltaTime)
{
}

World* ActorComponent::GetWorld() const
{
	return Owner->GetWorld();
}
