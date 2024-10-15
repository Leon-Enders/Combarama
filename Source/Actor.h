#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"
#include "Avatar.h"

//TODO: Move Rotation into from Avatar to Actor, since we want to use the Actor rotation for stuff
class Actor
{

public:
	Actor() {};
	Actor(const Vector2& InPosition);


	void UpdatePosition(const Vector2& NewPosition);
	void UpdateVelocity(Vector2 NewVelocity);
	void ReceiveMouseInput(Vector2 TargetPosition);
	void UpdateRotation();
	void Update(float DeltaTime);

	void Draw(SDL_Renderer* GameRenderer);


private:

	// Physics
	Vector2 Position;
	float Rotation = 0.f;
	Vector2 Velocity = {0.f, 0.f};
	float MoveSpeed = 0.5f;

	Vector2 LastMousePosition;

	// Rendering
	std::unique_ptr<Avatar> ActorAvatar = nullptr;

};