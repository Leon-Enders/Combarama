#include "Collider.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_log.h"
#include "../System/CollisionSystem.h"

Collider::Collider(const Vector2& Origin, float InWidth, float InHeight)
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
	OnCollisionEnterDelegate(Other);
}

void Collider::OnCollisionExit(const Collider& Other)
{
	OnCollisionExitDelegate(Other);
}
