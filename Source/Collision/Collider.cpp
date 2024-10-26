#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Actor.h"

Collider::Collider(Actor* InOwningActor, const Vector2& Origin, float InWidth, float InHeight)
	:
	OwningActor(InOwningActor)
{
	ColliderBox.w = InWidth;
	ColliderBox.h = InHeight;

	CenterOffset.X = InWidth / 2;
	CenterOffset.Y = InHeight / 2;

	ColliderBox.x = Origin.X - CenterOffset.X;
	ColliderBox.y = Origin.Y - CenterOffset.Y;

	CollisionSystem::Get().AddCollider(*this);
}

Collider::~Collider()
{
	//Remove from CollisionSystem
}

void Collider::UpdatePosition(const Vector2& NewPosition)
{
	ColliderBox.x = NewPosition.X - CenterOffset.X;
	ColliderBox.y = NewPosition.Y - CenterOffset.Y;	
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	if (DrawDebug)
	{
		SDL_RenderRect(Renderer, &ColliderBox);
	}
}

void Collider::OnCollisionExit(const Collider& Other)
{
	OnCollisionExitDelegate(Other);
}

void Collider::HandleCollision(const Collider& Other,const SDL_FRect& OtherBox, const SDL_FRect& Intersection)
{
	ECollisionFlags CollisionResult;


	float OverlapX = Intersection.w;
	float OverlapY = Intersection.h;

	if (OverlapX < OverlapY)
	{

		if (ColliderBox.x < OtherBox.x)
		{
			OwningActor->SetPosition(OwningActor->GetPosition() - Vector2(OverlapX, 0.f) * 0.5f);
			CollisionResult = ECollisionFlags::Left;
		}
		else
		{
			OwningActor->SetPosition(OwningActor->GetPosition() + Vector2(OverlapX, 0.f) * 0.5f);
			CollisionResult = ECollisionFlags::Right;
		}
	}
	else {

		if (ColliderBox.y < OtherBox.y)
		{
			OwningActor->SetPosition(OwningActor->GetPosition() - Vector2(0.f, OverlapY) * 0.5f);
			CollisionResult = ECollisionFlags::Top;
		}
		else
		{
			OwningActor->SetPosition(OwningActor->GetPosition() + Vector2(0.f, OverlapY) * 0.5f);
			CollisionResult = ECollisionFlags::Bottom;
		}
	}


	OnCollisionEnterDelegate(Other, CollisionResult);
}

