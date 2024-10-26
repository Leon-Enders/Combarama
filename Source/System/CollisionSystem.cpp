#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::CheckForPossibleCollisions(float FixedDeltaTime)
{
	//Cache Intersection Rectangle
	SDL_FRect Intersection;

	for(const auto & ActiveCollider : ActiveColliders)
	{
		for (const auto& OtherCollider : ActiveColliders)
		{
			if (&ActiveCollider == &OtherCollider) break;

			if (SDL_GetRectIntersectionFloat(&ActiveCollider.get().GetColliderBox(), &OtherCollider.get().GetColliderBox(), &Intersection))
			{
				ActiveCollider.get().OnCollisionEnter(OtherCollider, Intersection);
			}
		}
	}
}

void CollisionSystem::Update(float DeltaTime)
{
	
	CheckForPossibleCollisions(DeltaTime);

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

