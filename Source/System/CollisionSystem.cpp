#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::CheckForPossibleCollisions(float FixedDeltaTime)
{
	for(const auto & ActiveCollider : ActiveColliders)
	{
		for (const auto& aCollider : ActiveColliders)
		{
			if (&ActiveCollider == &aCollider) break;

			if (SDL_HasRectIntersectionFloat(ActiveCollider.get().GetColliderBox(), aCollider.get().GetColliderBox()))
			{
				ActiveCollider.get().OnCollisionEnter(ActiveCollider);
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
