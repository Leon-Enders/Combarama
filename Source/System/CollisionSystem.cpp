#include "CollisionSystem.h"
#include "SDL3/SDL_render.h"
#include "../Collision/Collider.h"
#include <unordered_map>
#include "../Entity/Character.h"

CollisionSystem CollisionSystem::Instance;

void CollisionSystem::CheckForPossibleCollisions(float DeltaTime)
{
	for (const auto& ActiveCollider : ActiveColliders)
	{
		Vector2 OldPosition = ActiveCollider.get().GetPosition();

		Vector2 NewPosition = ActiveCollider.get().GetCharacter().GetPosition() +
			ActiveCollider.get().GetCharacter().GetVecolity() * DeltaTime * 500.f;

		SDL_FRect SimulatedRect = ActiveCollider.get().GetColliderBoxCopy();
		SimulatedRect.x =+ NewPosition.X - ActiveCollider.get().GetOffset().X;
		SimulatedRect.y =+ NewPosition.Y - ActiveCollider.get().GetOffset().Y;


		for (const auto& aCollider : ActiveColliders)
		{
			if (&ActiveCollider == &aCollider) continue;

			if (SDL_HasRectIntersectionFloat(&SimulatedRect, aCollider.get().GetColliderBox()))
			{
				ActiveCollider.get().OnBlockNextMove();
			}
		}

	}
}

void CollisionSystem::Update(float DeltaTime)
{
	
	//for (const auto& ActiveCollider : ActiveColliders)
	//{
	//	for (const auto& aCollider : ActiveColliders)
	//	{
	//		if (&ActiveCollider == &aCollider) break;
	//
	//		if (SDL_HasRectIntersectionFloat(ActiveCollider.get().GetColliderBox(), aCollider.get().GetColliderBox()))
	//		{
	//			ActiveCollider.get().OnCollisionEnter(aCollider);
	//		}
	//		else
	//		{
	//			ActiveCollider.get().OnCollisionExit(aCollider);
	//		}
	//	}
	//}

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
