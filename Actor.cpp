#include "Actor.h"
#include <SDL3/SDL_log.h>

Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	Awake();
}

void Actor::Awake()
{
	// Create Circle as visual representation for actor
	SDL_Vertex Center;
	Center.position.x = Position.X;
	Center.position.y = Position.Y;


	Circle ACircle = Circle(Radius, Center, ActorColor);
	ACircle.InitializeCircle();

	ActorCircle = std::make_unique<Circle>(ACircle);
}

void Actor::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;

	ActorCircle->UpdatePosition(Position);
}

void Actor::Draw(SDL_Renderer* GameRenderer)
{
	ActorCircle->Draw(GameRenderer);
}
