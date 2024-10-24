#include "Collider.h"
#include "../Entity/Actor.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"
#include "../Entity/Character.h"

Collider::Collider(Character& InOwningCharacter, const Vector2& Origin, float InWidth, float InHeight)
	:
	OwningActor(std::ref(InOwningCharacter))
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

void Collider::OnCollisionEnter(const Collider& Other)
{
	SDL_Log("Collision!");
}

void Collider::OnCollisionExit(const Collider& Other)
{
	//OwningActor.get().SetCanMove(true);
}

void Collider::OnBlockNextMove()
{
	OwningActor.get().SetCanMove(false);
}
