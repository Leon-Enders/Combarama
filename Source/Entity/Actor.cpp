#include "Actor.h"
#include "../World/World.h"

Actor::Actor(World* GameWorld, const Transform& InTransform)
	:
	GameObject(GameWorld),
	EntityTransform(InTransform),
	OwningWorld(GameWorld)
{
}

void Actor::OnOverlapBegin(std::weak_ptr<Collider> Other)
{

}

