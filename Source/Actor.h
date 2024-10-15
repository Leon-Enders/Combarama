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


	void UpdatePosition(const Vector2& NewPosition);
	void UpdateVelocity(Vector2 NewVelocity);
	void Update(float DeltaTime);

	void Draw(SDL_Renderer* GameRenderer);


private:

	// Physics
	Vector2 Position;
	Vector2 Velocity = {0.f, 0.f};

	// Rendering
	std::unique_ptr<Avatar> ActorAvatar = nullptr;

};