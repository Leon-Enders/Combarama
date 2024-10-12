#include "Actor.h"
#include <SDL3/SDL_log.h>

Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	ActorAvatar = std::make_unique<Avatar>(Avatar(Position));
}

void Actor::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;

	ActorAvatar->UpdatePosition(Position);
}

void Actor::Draw(SDL_Renderer* GameRenderer)
{
	ActorAvatar->Draw(GameRenderer);
}
