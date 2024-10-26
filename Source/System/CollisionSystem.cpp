#include "CollisionSystem.h"
#include <unordered_map>
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"

struct CollisionEvent {
	Collider& ActiveCollider;
	const Collider& OtherCollider;
	const SDL_FRect OtherColliderBox;
	const SDL_FRect Intersection;
};



CollisionSystem CollisionSystem::Instance;

void CollisionSystem::CheckForPossibleCollisions(float FixedDeltaTime)
{
	SDL_FRect Intersection;
	// Cache all Collider which overlap
	//std::unordered_map<std::reference_wrapper<Collider>, CollisionEvent> ColliderToCollisionEvents;
	std::vector<CollisionEvent> CollisionEvents;

	for(const auto & ActiveCollider : ActiveColliders)
	{
		for (const auto& OtherCollider : ActiveColliders)
		{
			if (&ActiveCollider == &OtherCollider) continue;

			if (SDL_GetRectIntersectionFloat(&ActiveCollider.get().GetColliderBox(), &OtherCollider.get().GetColliderBox(), &Intersection))
			{
				//ColliderToCollisionEvents.insert({ ActiveCollider, {OtherCollider.get(), Intersection}});
				CollisionEvents.push_back({ActiveCollider.get() ,OtherCollider.get(),OtherCollider.get().GetColliderBox(), Intersection});
			}
		}
	}

	for (auto& event : CollisionEvents)
	{
		//You can still push other ppl because you calculate with different positions, after the first
		event.ActiveCollider.HandleCollision(event.OtherCollider,event.OtherColliderBox, event.Intersection);
	}
	//for (auto& Pair : ColliderToCollisionEvents)
	//{
	//	Pair.first.get().HandleCollision(Pair.second.OtherCollider, Pair.second.Intersection);
	//}
}

void CollisionSystem::Update(float FixedDeltaTime)
{
	
	CheckForPossibleCollisions(FixedDeltaTime);

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

