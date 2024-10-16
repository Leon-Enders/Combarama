#include "Actor.h"
#include <SDL3/SDL_log.h>
#include <cmath>


Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	ActorAvatar = std::make_unique<Avatar>(Position);	
}

void Actor::Initialize()
{

}

void Actor::UpdatePosition(float DeltaTime)
{
	Position += Velocity * DeltaTime * Speed;

	ActorAvatar->UpdatePosition(Position);
}

void Actor::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor)
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

void Actor::Draw(SDL_Renderer* GameRenderer)
{
	ActorAvatar->Draw(GameRenderer);
}
