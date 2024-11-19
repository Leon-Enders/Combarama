#include "ActorComponent.h"

void ActorComponent::Initialize(Actor* InOwner)
{
	Owner = InOwner;
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
