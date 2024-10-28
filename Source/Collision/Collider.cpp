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
	CollisionSystem::Get().RemoveCollider(*this);
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

void Collider::HandleCollision(const Collider& Other,const SDL_FRect& Intersection)
{
	//TODO Refactor for better performance
	//TODO: Check cast and return of not character, can ignore B velocity if object is static
	float OverlapX = Intersection.w;
	float OverlapY = Intersection.h;

	SDL_FRect OtherBoxCollider = Other.GetColliderBox();

	Character* CharacA = dynamic_cast<Character*>(OwningActor);
	Character* CharacB = dynamic_cast<Character*>(Other.OwningActor); 

	Vector2 CorrectedPosition = CharacA->GetPosition();
	Vector2 VelocityA = CharacA->GetVecolity();
	Vector2 VelocityB = CharacB->GetVecolity();

	
	float TotalVelocityX = std::abs(VelocityA.X) + std::abs(VelocityB.X);
	float TotalVelocityY = std::abs(VelocityA.Y) + std::abs(VelocityB.Y);


	float PushBackScale_X = (TotalVelocityX > 0) ? std::abs(VelocityA.X) / TotalVelocityX : 0.5f;
	float PushBackScale_Y = (TotalVelocityY > 0) ? std::abs(VelocityA.Y) / TotalVelocityY : 0.5f;
	
	if (OverlapX < OverlapY)
	{
		if (ColliderBox.x < OtherBoxCollider.x)
		{
			CorrectedPosition.X -= OverlapX * PushBackScale_X;
		}
		else {
			CorrectedPosition.X += OverlapX * PushBackScale_X;
		}
	}
	else {
		if (ColliderBox.y < OtherBoxCollider.y)
		{
			CorrectedPosition.Y -= OverlapY * PushBackScale_Y;
		}
		else 
		{
			CorrectedPosition.Y += OverlapY * PushBackScale_Y;
		}
	}

	CharacA->SetPosition(CorrectedPosition);
}

