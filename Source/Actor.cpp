#include "Actor.h"
#include <SDL3/SDL_log.h>
#include <cmath>


Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	ActorAvatar = std::make_unique<Avatar>(Position);	
}

void Actor::UpdatePosition(const Vector2& NewPosition)
{
	//Position = NewPosition;
	//ActorAvatar->UpdatePosition(Position);
}

void Actor::UpdateVelocity(Vector2 NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::UpdateRotation(Vector2 TargetPosition)
{

	float DeltaX = Position.X- TargetPosition.X;
	float DeltaY = Position.Y - TargetPosition.Y;

	// Calculate the angle in radians
	float AngleInRad = std::atan2f(DeltaX, DeltaY);

	ActorAvatar->Rotate(AngleInRad);
}





void Actor::Update(float DeltaTime)
{
	//Position += Velocity * DeltaTime;

	//ActorAvatar->UpdatePosition(Position);
}

void Actor::Draw(SDL_Renderer* GameRenderer)
{
	ActorAvatar->Draw(GameRenderer);
}
