#include "CollisionSystem.h"
#include <algorithm>
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"



struct CollisionEventInfo 
{
	Collider& ActiveCollider;
	const Collider& OtherCollider;
	const SDL_FRect Intersection;
};



CollisionSystem CollisionSystem::Instance;

void CollisionSystem::Update(float FixedDeltaTime)
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		ActiveCollider.get().FixedUpdate(FixedDeltaTime);
	}
	CheckForPossibleCollisions(FixedDeltaTime);

}

void CollisionSystem::CheckForPossibleCollisions(float FixedDeltaTime)
{
	SDL_FRect Intersection;

	std::vector<CollisionEventInfo> CollisionEvents;

	for (const auto& ActiveCollider : ActiveColliders)
	{
		for (const auto& OtherCollider : ActiveColliders)
		{
			if (&ActiveCollider == &OtherCollider) continue;

			if (SDL_GetRectIntersectionFloat(&ActiveCollider.get().GetColliderBox(), &OtherCollider.get().GetColliderBox(), &Intersection))
			{
				CollisionEvents.push_back({ ActiveCollider.get() ,OtherCollider.get(), Intersection });
			}
		}
	}

	for (auto& Event : CollisionEvents)
	{
		Event.ActiveCollider.HandleCollision(Event.OtherCollider, Event.Intersection);
	}
}

void CollisionSystem::Draw(SDL_Renderer* GameRenderer)
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		ActiveCollider.get().Draw(GameRenderer);
	}
}

void CollisionSystem::AddCollider(Collider& ColliderToAdd)
{
	ActiveColliders.push_back(std::ref(ColliderToAdd));
}

void CollisionSystem::RemoveCollider(Collider& ColliderToRemove)
{
	std::erase_if(ActiveColliders, [&](std::reference_wrapper<Collider> ActiveCollider)
		{
			return &ActiveCollider.get() == &ColliderToRemove;
		});
}

