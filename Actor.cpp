#include "Actor.h"
#include <SDL3/SDL_log.h>

Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	const SDL_FRect Rect = { Position.X, Position.Y, Width, Height };
	
	ActorRect = std::make_unique<SDL_FRect>(Rect);
}

void Actor::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;

	ActorRect->x = static_cast<int>(Position.X);
	ActorRect->y = static_cast<int>(Position.Y);
}

void Actor::Draw(SDL_Window* GameWindow, SDL_Renderer* GameRenderer)
{
	SDL_SetRenderDrawColor(GameRenderer, ActorColor.r, ActorColor.g, ActorColor.b, ActorColor.a);
	SDL_RenderFillRect(GameRenderer, ActorRect.get());
}
