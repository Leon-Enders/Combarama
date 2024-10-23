#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"
#include <unordered_map>

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::Update()
{
	std::unordered_map<Collider*, Collider*> TriggeredColliders;

	for (const auto& ActiveCollider : ActiveColliders)
	{
		for (const auto& aCollider : ActiveColliders)
		{
			if (ActiveCollider == aCollider) break;

			if (SDL_HasRectIntersectionFloat(ActiveCollider->GetColliderBox(), aCollider->GetColliderBox()))
			{
				TriggeredColliders.insert({ ActiveCollider, aCollider });
			}
		}
	}
	for (const auto& ColliderPair : TriggeredColliders)
	{
		ColliderPair.first->OnCollisionEnter(ColliderPair.second);
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
