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
	SDL_Vertex CircleCenter;
	CircleCenter.position.x = Position.X;
	CircleCenter.position.y = Position.Y;

	Circle ACircle = Circle(Radius, CircleCenter, ActorColor);
	ACircle.InitializeCircle();

	ActorCircle = std::make_unique<Circle>(ACircle);


	// Create a Rectangle as visual representation for the direction the actor is looking
	SDL_Vertex RectCenter;
	RectCenter.position.x = Position.X;
	RectCenter.position.y = Position.Y - 25.f;

	SDL_FColor RectColor = { 0.f, 0.3f,0.6f,1.f };


	Rectangle ARect = Rectangle(RectCenter,20.f, 15.f, RectColor);
	ARect.InitializeRectangle();

	ActorRectangle= std::make_unique<Rectangle>(ARect);
}

void Actor::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;

	ActorCircle->UpdatePosition(Position);
	ActorRectangle->UpdatePosition(Position);
}

void Actor::Draw(SDL_Renderer* GameRenderer)
{
	ActorCircle->Draw(GameRenderer);
	ActorRectangle->Draw(GameRenderer);
}
