#include "ActorComponent.h"
#include "../Entity/Actor.h"

ActorComponent::~ActorComponent()
{
}

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

const Transform& ActorComponent::GetWorldTransform()const
{
	return Owner->GetTransform();
}
