#include "CollisionSystem.h"
#include <algorithm>
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"
#include "../Entity/Actor.h"



struct CollisionEventInfo 
{
	std::weak_ptr<Collider> wActiveCollider;
	std::weak_ptr<Collider> wOtherCollider;
	const SDL_FRect Intersection;
};



CollisionSystem CollisionSystem::Instance;

void CollisionSystem::Update(float FixedDeltaTime)
{
	for (auto it = ActiveColliders.begin();it != ActiveColliders.end();)
	{
		if (auto sActiveCollider = it->lock())
		{
			sActiveCollider->FixedUpdate(FixedDeltaTime);
			it++;
		}
		else
		{
			it = ActiveColliders.erase(it);
		}
	}
	CheckForPossibleCollisions(FixedDeltaTime);

}

void CollisionSystem::CheckForPossibleCollisions(float FixedDeltaTime)
{
	SDL_FRect Intersection;

	std::vector<CollisionEventInfo> CollisionEvents;

	for (const auto& ActiveCollider : ActiveColliders)
	{
		if (auto sActiveCollider = ActiveCollider.lock())
		{
			for (const auto& OtherCollider : ActiveColliders)
			{
				if (auto sOtherCollider = OtherCollider.lock())
				{
					if (sActiveCollider == sOtherCollider) continue;

					if (SDL_GetRectIntersectionFloat(&sActiveCollider->GetColliderBox(), &sOtherCollider->GetColliderBox(), &Intersection))
					{
						CollisionEvents.push_back({ ActiveCollider ,OtherCollider, Intersection });
					}
				}
			}
		}
		
	}

	for (auto& Event : CollisionEvents)
	{
		if (auto sActiveCollider = Event.wActiveCollider.lock())
		{
			if (auto sOtherCollider = Event.wOtherCollider.lock())
			{
				sActiveCollider->HandleCollision(sOtherCollider, Event.Intersection);
			}
		}
	}
}

void CollisionSystem::Draw(SDL_Renderer* GameRenderer)
{
	SDL_SetRenderDrawColor(GameRenderer, 255, 0, 0, 255);


	for (auto it = ActiveColliders.begin();it != ActiveColliders.end();)
	{
		if (auto sActiveCollider = it->lock())
		{
			sActiveCollider->Draw(GameRenderer);
			it++;
		}
		else
		{
			it = ActiveColliders.erase(it);
		}
	}
}


void CollisionSystem::AddCollider(std::shared_ptr<Collider> ColliderToAdd)
{
	ActiveColliders.push_back(ColliderToAdd);
}

std::vector<Collider> CollisionSystem::GetColliderInCone(std::weak_ptr<Actor> Instigator, const Vector2& Direction, float Height, float Angle)
{

	//TODO: Filter for character here with GetAllCharacters from World since Obstacles,Projectiles etc. dont need to be iterated
	std::vector<Collider> OverlappedColliders;

	if (auto sInstigator = Instigator.lock())
	{
		//Cache Actor Position
		Vector2 ActorPosition = sInstigator->GetPosition();

		for (const auto& ActiveCollider : ActiveColliders)
		{
			if (auto sActiveCollider = ActiveCollider.lock())
			{
				if (sActiveCollider->GetOwningActor().lock() == sInstigator) continue;

				SDL_FRect BoxCollider = sActiveCollider->GetColliderBox();


				Vector2 Corners[4] =
				{
					Vector2(BoxCollider.x, BoxCollider.y),
					Vector2(BoxCollider.x + BoxCollider.w, BoxCollider.y),
					Vector2(BoxCollider.x, BoxCollider.y + BoxCollider.h),
					Vector2(BoxCollider.x + BoxCollider.w, BoxCollider.y + BoxCollider.h)
				};

				bool HasOverlap = false;
				for (const auto& Corner : Corners)
				{

					Vector2 ToCorner = Corner - ActorPosition;


					float distance = ToCorner.Size();
					if (distance > Height) continue;


					Vector2 NormalizedDirection = Direction.Normalize();
					Vector2 NormalizedToCorner = ToCorner.Normalize();


					float DotProduct = NormalizedDirection.Dot(NormalizedToCorner);
					float AngleToCorner = std::acos(DotProduct);


					if (AngleToCorner <= Angle)
					{
						HasOverlap = true;
					}
				}
				if (HasOverlap)
				{
					OverlappedColliders.push_back(*sActiveCollider.get());
				}
			}

		}
	}
	

	


	return OverlappedColliders;
}

