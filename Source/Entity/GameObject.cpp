#include "GameObject.h"

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
}

void GameObject::Destroy()
{
	OnDestroyDelegate.Broadcast();
	//GetWorld()->RemoveActor(this);
}
