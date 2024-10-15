#include "PlayerCharacter.h"
#include "ColorHelper.h"

PlayerCharacter::PlayerCharacter(const Vector2& InPosition)
	:
	Character(InPosition)
{
	Position = InPosition;
	
}

void PlayerCharacter::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{
	LastMousePosition = TargetPosition;
}

void PlayerCharacter::Initialize()
{
	SetColor(COLOR_BLUE, COLOR_LIGHTBLUE);
}

void PlayerCharacter::UpdateRotation()
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
