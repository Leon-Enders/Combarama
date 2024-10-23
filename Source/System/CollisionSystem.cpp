#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"
#include <unordered_map>

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::Update()
{
	
	for (const auto& ActiveCollider : ActiveColliders)
	{
		for (const auto& aCollider : ActiveColliders)
		{
			if (&ActiveCollider == &aCollider) break;

			if (SDL_HasRectIntersectionFloat(ActiveCollider.get().GetColliderBox(), aCollider.get().GetColliderBox()))
			{
				ActiveCollider.get().OnCollisionEnter(aCollider);
			}
		}
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
	ActiveColliders.push_back(ColliderToAdd);
}
