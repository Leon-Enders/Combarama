#include "Actor.h"
#include "../Subsystem/ActorSystem.h"


Actor::Actor(const Transform& InTransform)
	:
	EntityTransform(InTransform)
{
	ActorSystem::Get().AddActor(this);
}

Actor::~Actor()
{
	ActorSystem::Get().RemoveActor(this);
}

void Actor::Initialize()
{

}


void Actor::Update(float DeltaTime)
{

}
