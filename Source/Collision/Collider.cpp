#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Actor.h"
#include "../Entity/Character.h"

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

void Collider::FixedUpdate(float FixedDeltaTime)
{
	ColliderBox.x = OwningActor->GetPosition().X - CenterOffset.X;
	ColliderBox.y = OwningActor->GetPosition().Y - CenterOffset.Y;
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	ColliderBox.x = OwningActor->GetPosition().X - CenterOffset.X;
	ColliderBox.y = OwningActor->GetPosition().Y - CenterOffset.Y;
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


	Character* Charac = dynamic_cast<Character*>(OwningActor);
	Vector2 OffsetVector = OwningActor->GetPosition();
	if (OverlapX < OverlapY)
	{

		if (ColliderBox.x < OtherBox.x)
		{
			OffsetVector.X -= + Charac->GetVecolity().X * 0.02f;
			CollisionResult = ECollisionFlags::Left;
		}
		else
		{
			OffsetVector.X += - Charac->GetVecolity().X * 0.02f;
			CollisionResult = ECollisionFlags::Right;
		}
	}
	else {

		if (ColliderBox.y < OtherBox.y)
		{
			OffsetVector.Y -= + Charac->GetVecolity().Y * 0.02f;
			CollisionResult = ECollisionFlags::Top;
		}
		else
		{
			OffsetVector.Y +=  - Charac->GetVecolity().Y * 0.02f;
			CollisionResult = ECollisionFlags::Bottom;
		}

	
	}

	OwningActor->SetPosition(OffsetVector);
}

