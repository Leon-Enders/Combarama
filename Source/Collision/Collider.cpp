#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Actor.h"
#include "../Entity/Character.h"

Collider::Collider(Actor* InOwningActor, float InWidth, float InHeight)
	:
	OwningActor(InOwningActor),
	BoundingBo(OwningActor->GetPosition(),InWidth/2.f,InHeight/2.f)
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

	BoundingBo.Update(OwningActor->GetTransform());
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	//ColliderBox.x = OwningActor->GetPosition().X - CenterOffset.X;
	//ColliderBox.y = OwningActor->GetPosition().Y - CenterOffset.Y;
	if (DrawDebug)
	{
		const auto& points = BoundingBo.GetBoundingBoxPoints();
		// Draw lines between each consecutive point to form the box
		SDL_RenderLine(Renderer, points[0].X, points[0].Y, points[1].X, points[1].Y); // Top edge
		SDL_RenderLine(Renderer, points[1].X, points[1].Y, points[2].X, points[2].Y); // Right edge
		SDL_RenderLine(Renderer, points[2].X, points[2].Y, points[3].X, points[3].Y); // Bottom edge
		SDL_RenderLine(Renderer, points[3].X, points[3].Y, points[0].X, points[0].Y); // Left edge
	}
}

void Collider::OnCollisionExit(const Collider& Other)
{
	OnCollisionExitDelegate(Other);
}

void Collider::HandleCollisionBounding(const Collider& Other)
{
	float overlapX, overlapY;

	if (BoundingBo.IsCollidingWith(Other.BoundingBo, overlapX, overlapY))
	{
		SDL_Log("Collide!");

		Vector2 CorrectedPosition = OwningActor->GetPosition();
		Vector2 VelocityA = dynamic_cast<Character*>(OwningActor)->GetVelocity();
		Vector2 VelocityB = dynamic_cast<Character*>(Other.OwningActor)->GetVelocity();

		if (std::abs(overlapX) < std::abs(overlapY))
		{
			// Resolve along X-axis
			if (ColliderBox.x < Other.ColliderBox.x)
			{
				CorrectedPosition.X -= overlapX; // Push to the left
			}
			else
			{
				CorrectedPosition.X += overlapX; // Push to the right
			}
		}
		else
		{
			// Resolve along Y-axis
			if (ColliderBox.y < Other.ColliderBox.y)
			{
				CorrectedPosition.Y -= overlapY; // Push upwards
			}
			else
			{
				CorrectedPosition.Y += overlapY; // Push downwards
			}
		}
		dynamic_cast<Character*>(OwningActor)->SetPosition(CorrectedPosition);
	}
}

void Collider::HandleCollision(const Collider& Other,const SDL_FRect& Intersection)
{
	//TODO Refactor for better performance
	//TODO: Check cast and return of not character, can ignore B velocity if object is static
	float OverlapX = Intersection.w;
	float OverlapY = Intersection.h;

	SDL_FRect OtherBoxCollider = Other.GetColliderBox();

	if (Character* CharacterA = dynamic_cast<Character*>(OwningActor))
	{
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

		OnCollisionEnterDelegate(Other);
	}
}

