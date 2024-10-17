#include "PlayerCharacter.h"
#include "../Utility/ColorHelper.h"
#include "../Utility/MathConstants.h"

PlayerCharacter::PlayerCharacter(const Vector2& InPosition)
	:
	Character(InPosition)
{
	Position = InPosition;

	//Construct a Sword
	RenderedSword = std::make_unique<Sword>(InPosition, Rotation, Vector2(0.f,100.f));
}

void PlayerCharacter::UpdateVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

void PlayerCharacter::ReceiveMouseInput(const Vector2& TargetPosition)
{
	float DeltaX = Position.X - TargetPosition.X;
	float DeltaY = Position.Y - TargetPosition.Y;
	
	// Calculate the angle in radians
	float AngleInRad = std::atan2f(DeltaX, DeltaY);
	
	
	if (AngleInRad < 0)
	{
		AngleInRad += static_cast<float>(2 * M_PI);
	}
	
	float DeltaRotation = Rotation - AngleInRad;
	
	Rotation = AngleInRad;

	OwnedRenderComponent->UpdateRotation(DeltaRotation);
	RenderedSword->GetRenderComponent()->UpdateRotation(DeltaRotation);
}

void PlayerCharacter::Initialize()
{
	SetColor(COLOR_BLUE, COLOR_LIGHTBLUE);
}

void PlayerCharacter::UpdatePosition(float DeltaTime)
{
	Actor::UpdatePosition(DeltaTime);

	RenderedSword->GetRenderComponent()->UpdatePosition(Position);
}

void PlayerCharacter::UpdateRotation()
{
	/*
	* This can be used to create a Target Lock On mechanic
	* We want strafing for our player though
	*/
	
	//float DeltaX = Position.X - LastMousePosition.X;
	//float DeltaY = Position.Y - LastMousePosition.Y;
	//
	//// Calculate the angle in radians
	//float AngleInRad = std::atan2f(DeltaX, DeltaY);
	//
	//
	//if (AngleInRad < 0)
	//{
	//	AngleInRad += static_cast<float>(2 * M_PI);
	//}
	//
	//float DeltaRotation = Rotation - AngleInRad;
	//
	//Rotation = AngleInRad;
	//ActorAvatar->UpdateRotation(DeltaRotation);
}
