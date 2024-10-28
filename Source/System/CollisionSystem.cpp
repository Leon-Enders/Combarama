#include "CollisionSystem.h"
#include <algorithm>
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"
#include "../Entity/Actor.h"



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
	SDL_SetRenderDrawColor(GameRenderer, 255, 0, 0, 255);
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

Collider* CollisionSystem::GetColliderInCone(Actor* Instigator, const Vector2& Direction, float Height, float Angle)
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		if (ActiveCollider.get().GetOwningActor() == Instigator) continue;  // Skip self-collisions

		SDL_FRect BoxCollider = ActiveCollider.get().GetColliderBox();

		// Get the four corners of the collider's box
		Vector2 corners[4] = 
		{
			Vector2(BoxCollider.x, BoxCollider.y),                                                   // Top-left corner
			Vector2(BoxCollider.x +BoxCollider.w, BoxCollider.y),  // Top-right corner
			Vector2(BoxCollider.x, BoxCollider.y + BoxCollider.h), // Bottom-left corner
			Vector2(BoxCollider.x + BoxCollider.w, BoxCollider.y + BoxCollider.h) // Bottom-right corner
		};

		for (const auto& corner : corners)
		{
			// Vector from Instigator to corner
			Vector2 toCorner = corner - Instigator->GetPosition();

			// Calculate the distance to check if within cone's height
			float distance = toCorner.Size();
			if (distance > Height) continue; // Corner is too far

			// Normalize direction vectors to calculate the angle
			Vector2 normalizedDirection = Direction.Normalize();
			Vector2 normalizedToCorner = toCorner.Normalize();

			// Calculate the angle between the direction and the vector to the corner
			float dotProduct = normalizedDirection.Dot(normalizedToCorner);
			float angleToCorner = std::acos(dotProduct); // Angle in radians

			// Check if this angle is within the half-angle of the cone
			if (angleToCorner <= Angle)
			{
				return &ActiveCollider.get(); // Found a collider within the cone
			}
		}
	}

	// Return a default or null collider if no intersection found (depending on your design)
	return nullptr;
}

