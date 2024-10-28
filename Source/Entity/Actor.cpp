#include "Actor.h"


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

Actor::~Actor()
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

void Actor::DrawDebug()
{
}
