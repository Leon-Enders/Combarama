#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Actor.h"
#include "../Entity/Character.h"
#include "../Entity/Projectile.h"

Collider::Collider(Actor* InOwningActor, float InWidth, float InHeight)
	:
	OwningActor(InOwningActor)
{
	ColliderBox.w = InWidth;
	ColliderBox.h = InHeight;

	CenterOffset.X = InWidth / 2;
	CenterOffset.Y = InHeight / 2;

	ColliderBox.x = OwningActor->GetPosition().X - CenterOffset.X;
	ColliderBox.y = OwningActor->GetPosition().Y - CenterOffset.Y;

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
	
	if (!OwningActor)return;

	float OverlapX = Intersection.w;
	float OverlapY = Intersection.h;

	SDL_FRect OtherBoxCollider = Other.GetColliderBox();

	if (Character* CharacterA = dynamic_cast<Character*>(OwningActor))
	{
		//Check if the other collider is attached to a projectile if so just return;
		if (Projectile* ProjectileB = dynamic_cast<Projectile*>(Other.GetOwningActor()))
		{
			return;
		}

		Vector2 CorrectedPosition = CharacterA->GetPosition();
		Vector2 VelocityA = CharacterA->GetVelocity();

		if (Character* CharacterB = dynamic_cast<Character*>(Other.OwningActor))
		{
			Vector2 VelocityB = CharacterB->GetVelocity();


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
		}
		else
		{
			float TotalVelocityX = std::abs(VelocityA.X);
			float TotalVelocityY = std::abs(VelocityA.Y);

			if (OverlapX < OverlapY)
			{
				if (ColliderBox.x < OtherBoxCollider.x)
				{
					CorrectedPosition.X -= OverlapX;
				}
				else {
					CorrectedPosition.X += OverlapX;
				}
			}
			else {
				if (ColliderBox.y < OtherBoxCollider.y)
				{
					CorrectedPosition.Y -= OverlapY;
				}
				else
				{
					CorrectedPosition.Y += OverlapY;
				}
			}
		}
		
		CharacterA->SetPosition(CorrectedPosition);
	}

	OnCollisionEntererDelegate.Invoke(Other);
	
	
}

