#include "Actor.h"
#include <SDL3/SDL_log.h>
#include "SDL3/SDL_pixels.h"
#include <cmath>


Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	ActorAvatar = std::make_unique<Avatar>(Position, Rotation);
	OwnedRenderComponent = ActorAvatar->GetRenderComponent();
}

void Actor::Initialize()
{

}

void Actor::UpdatePosition(float DeltaTime)
{
	Position += Velocity * DeltaTime * Speed;
	OwnedRenderComponent->UpdatePosition(Position);
}

void Actor::SetColor(const SDL_FColor& BodyColor, const SDL_FColor& HeadColor)
{
	ActorAvatar->SetColor(BodyColor, HeadColor);
}

void Actor::UpdateRotation()
{
	
}


void Actor::Update(float DeltaTime)
{
	UpdatePosition(DeltaTime);
	UpdateRotation();
}
