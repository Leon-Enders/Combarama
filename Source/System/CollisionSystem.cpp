#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::Update()
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		for (const auto& aCollider : ActiveColliders)
		{
			if (ActiveCollider == aCollider) break;

			if (SDL_HasRectIntersectionFloat(ActiveCollider->GetColliderBox(), aCollider->GetColliderBox()))
			{
				ActiveCollider->OnCollisionEnter(aCollider);
			}
		}
	}
}

void CollisionSystem::Draw(SDL_Renderer* GameRenderer)
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		ActiveCollider->Draw(GameRenderer);
	}
}

void CollisionSystem::AddCollider(Collider* ColliderToAdd)
{
	if (!ColliderToAdd) return;

	ActiveColliders.push_back(ColliderToAdd);
}
