#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"

CollisionSystem CollisionSystem::Instance;

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
