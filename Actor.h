#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"


class Actor
{

public:
	Actor(const Vector2& InPosition);
	~Actor() = default;

	void UpdateVelocity(const Vector2& NewVelocity);
	void Update(float DeltaTime);

	void Draw(SDL_Window* GameWindow, SDL_Renderer* GameRenderer);


private:

	// Physics
	Vector2 Position;
	Vector2 Velocity = {0.f, 0.f};
	
	static constexpr int Width = 64;
	static constexpr int Height = 64;

	// Rendering
	std::unique_ptr<SDL_FRect> ActorRect = nullptr;
	SDL_Color ActorColor = {255, 0, 0, 255};
};