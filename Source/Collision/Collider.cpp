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
	//TODO Refactor for better performance
	//TODO: Check cast and return of not character, can ignore B velocity if object is static
	float OverlapX = Intersection.w;
	float OverlapY = Intersection.h;

	Character* CharacA = dynamic_cast<Character*>(OwningActor);
	Character* CharacB = dynamic_cast<Character*>(Other.OwningActor); 

	Vector2 PositionA = CharacA->GetPosition();
	Vector2 VelocityA = CharacA->GetVecolity();
	Vector2 VelocityB = CharacB->GetVecolity();

	
	float TotalVelocityX = std::abs(VelocityA.X) + std::abs(VelocityB.X);
	float TotalVelocityY = std::abs(VelocityA.Y) + std::abs(VelocityB.Y);


	float PushBackScaleA_X = (TotalVelocityX > 0) ? std::abs(VelocityA.X) / TotalVelocityX : 0.5f;
	float PushBackScaleA_Y = (TotalVelocityY > 0) ? std::abs(VelocityA.Y) / TotalVelocityY : 0.5f;

	float PushBackScaleB_X = (TotalVelocityX > 0) ? std::abs(VelocityB.X) / TotalVelocityX : 0.5f;
	float PushBackScaleB_Y = (TotalVelocityY > 0) ? std::abs(VelocityB.Y) / TotalVelocityY : 0.5f;

	
	if (OverlapX < OverlapY)
	{
		if (ColliderBox.x < OtherBox.x)
		{
			PositionA.X -= OverlapX * PushBackScaleA_X;
		}
		else {
			PositionA.X += OverlapX * PushBackScaleA_X;
		}
	}
	else {
		if (ColliderBox.y < OtherBox.y) 
		{
			PositionA.Y -= OverlapY * PushBackScaleA_Y;
		}
		else 
		{
			PositionA.Y += OverlapY * PushBackScaleA_Y;
		}
	}

	CharacA->SetPosition(PositionA);
}

