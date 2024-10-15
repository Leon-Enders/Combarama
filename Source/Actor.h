#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"
#include "Avatar.h"

class Actor
{

public:
	Actor() {};
	Actor(const Vector2& InPosition);

	void Update(float DeltaTime);

	void UpdateVelocity(const Vector2& NewVelocity);
	void ReceiveMouseInput(const Vector2& TargetPosition);

	void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor);

	void Draw(SDL_Renderer* GameRenderer);

protected:
	void UpdatePosition(float DeltaTime);
	void UpdateRotation();

	// Rendering
	std::unique_ptr<Avatar> ActorAvatar = nullptr;
private:

	Vector2 Position;
	float Rotation = 0.f;
	Vector2 Velocity = {0.f, 0.f};

	float MoveSpeed = 0.5f;
	Vector2 LastMousePosition;
};