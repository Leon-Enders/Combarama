#include "Actor.h"
#include <SDL3/SDL_log.h>
#include <cmath>


Actor::Actor(const Vector2& InPosition)
	:
	Position(InPosition)
{
	ActorAvatar = std::make_unique<Avatar>(Position);	
}

void Actor::UpdatePosition(float DeltaTime)
{
	Position += Velocity * DeltaTime * MoveSpeed;

	ActorAvatar->UpdatePosition(Position);
}

void Actor::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void Actor::ReceiveMouseInput(const Vector2& TargetPosition)
{
	LastMousePosition = TargetPosition;
}

void Actor::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor)
{
	ActorAvatar->SetColor(BodyColor, HeadColor);
}

void Actor::UpdateRotation()
{
	float DeltaX = Position.X - LastMousePosition.X;
	float DeltaY = Position.Y - LastMousePosition.Y;

	// Calculate the angle in radians
	float AngleInRad = std::atan2f(DeltaX, DeltaY);


	if (AngleInRad < 0)
	{
		AngleInRad += static_cast<float>(2 * M_PI);
	}

	float DeltaRotation = Rotation - AngleInRad;

	Rotation = AngleInRad;
	ActorAvatar->UpdateRotation(DeltaRotation);
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
