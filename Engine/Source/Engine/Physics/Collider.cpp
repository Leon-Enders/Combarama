#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "CollisionSystem.h"
#include "../GameFramework/GameObject/Actor.h"
#include "../GameFramework/GameObject/Character/Character.h"
#include "../GameFramework/GameObject/Projectile.h"
#include "../../Core/Misc/CombaramaConstants.h"

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
		ColliderBox.y = sOwningActor->GetPosition().Y + CenterOffset.Y;
	}
	
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	if (auto sOwningActor = OwningActor.lock())
	{
		ColliderBox.x = sOwningActor->GetPosition().X - CenterOffset.X;
		ColliderBox.y = sOwningActor->GetPosition().Y + CenterOffset.Y;
	}

	float ScreenHalfWidth = Combarama::ViewportWidth / 2.f;
	float ScreenHalfHeight = Combarama::ViewportHeight / 2.f;
	float HalfWidth = ColliderBox.w/2.f;
	float HalfHeight = ColliderBox.h / 2.f;
	
	SDL_FRect RenderRect = ColliderBox;
	RenderRect.y *= -1.f;
	RenderRect.x += ScreenHalfWidth;
	RenderRect.y += ScreenHalfHeight;

	if (DrawDebug)
	{
		SDL_RenderRect(Renderer, &RenderRect);
	}
}

