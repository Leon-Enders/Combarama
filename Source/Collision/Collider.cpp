#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Actor.h"
#include "../Entity/Character.h"
#include "../Entity/Projectile.h"

Collider::Collider(std::shared_ptr<Actor> InOwningActor, float InWidth, float InHeight)
	:
	OwningActor(InOwningActor)
{
	ColliderBox.w = InWidth;
	ColliderBox.h = InHeight;

	CenterOffset.X = InWidth / 2;
	CenterOffset.Y = InHeight / 2;

	ColliderBox.x = InOwningActor->GetPosition().X - CenterOffset.X;
	ColliderBox.y = InOwningActor->GetPosition().Y - CenterOffset.Y;

}

//REMINDER: If no collider behaviour is working for a newly created collider the initialization was probably forgotten
//TODO: Create a system which automatically calls Initialization for Components
void Collider::Initialize()
{
	CollisionSystem::Get().AddCollider(shared_from_this());
}

void Collider::FixedUpdate(float FixedDeltaTime)
{
	if (auto sOwningActor = OwningActor.lock())
	{
		ColliderBox.x = sOwningActor->GetPosition().X - CenterOffset.X;
		ColliderBox.y = sOwningActor->GetPosition().Y - CenterOffset.Y;
	}
	
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	if (auto sOwningActor = OwningActor.lock())
	{
		ColliderBox.x = sOwningActor->GetPosition().X - CenterOffset.X;
		ColliderBox.y = sOwningActor->GetPosition().Y - CenterOffset.Y;
	}
	if (DrawDebug)
	{
		SDL_RenderRect(Renderer, &ColliderBox);
	}
}

void Collider::HandleCollision(std::shared_ptr<Collider> Other,const SDL_FRect& Intersection)
{
	//TODO Refactor for better performance
	//TODO: Check cast and return of not character, can ignore B velocity if object is static

	
	if (auto sOwningActor = OwningActor.lock())
	{

		float OverlapX = Intersection.w;
		float OverlapY = Intersection.h;

		SDL_FRect OtherBoxCollider = Other->GetColliderBox();

		//Check if this Collider is attached to a character
		if (auto sCharacterA = std::dynamic_pointer_cast<Character>(sOwningActor))
		{
			//Check if the other collider is attached to a projectile if so just return;
			//TODO: What blocks and what not blocks should be defined with CollisionChannels then this code can get removed
			if (auto sProjectileB = std::dynamic_pointer_cast<Projectile>(Other->GetOwningActor().lock()))
			{
				return;
			}

			// Cache the Position
			Vector2 CorrectedPosition = sCharacterA->GetPosition();

			if (auto sCharacterB = std::dynamic_pointer_cast<Character>(Other->GetOwningActor().lock()))
			{

				
				Vector2 VelocityA = sCharacterA->GetVelocity();
				Vector2 VelocityB = sCharacterB->GetVelocity();


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

			sCharacterA->SetPosition(CorrectedPosition);
		}

		OnOverlapBeginDelegate.Invoke(Other);

	}
}

