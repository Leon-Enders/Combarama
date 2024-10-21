#include "Actor.h"
#include "../Subsystem/ActorSystem.h"


Actor::Actor()
{
}

Actor::Actor(const Transform& InTransform)
	:
	EntityTransform(InTransform)
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
