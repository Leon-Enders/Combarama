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
		if (ActiveCollider.get().GetOwningActor() == Instigator) continue;

		SDL_FRect BoxCollider = ActiveCollider.get().GetColliderBox();

		
		Vector2 Corners[4] = 
		{
			Vector2(BoxCollider.x, BoxCollider.y),
			Vector2(BoxCollider.x +BoxCollider.w, BoxCollider.y),
			Vector2(BoxCollider.x, BoxCollider.y + BoxCollider.h),
			Vector2(BoxCollider.x + BoxCollider.w, BoxCollider.y + BoxCollider.h) 
		};

		for (const auto& Corner : Corners)
		{
			
			Vector2 ToCorner = Corner - Instigator->GetPosition();

			
			float distance = ToCorner.Size();
			if (distance > Height) continue; 

			
			Vector2 NormalizedDirection = Direction.Normalize();
			Vector2 NormalizedToCorner = ToCorner.Normalize();

			
			float DotProduct = NormalizedDirection.Dot(NormalizedToCorner);
			float AngleToCorner = std::acos(DotProduct); 

			
			if (AngleToCorner <= Angle)
			{
				return &ActiveCollider.get(); 
			}
		}
	}


	return nullptr;
}

std::vector<Collider> CollisionSystem::GetOverlapsInSphere(Actor* Instigator, float Radius)
{


	for (const auto& ActiveCollider : ActiveColliders)
	{
		if (ActiveCollider.get().GetOwningActor() == Instigator) continue; 

		SDL_FRect BoxCollider = ActiveCollider.get().GetColliderBox();
	}

	return std::vector<Collider>();
}

