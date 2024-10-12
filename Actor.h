#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"
#include "PrimitiveHelpers.h"


class Actor
{

public:
	Actor(const Vector2& InPosition);
	~Actor() = default;

	void Awake();


	void UpdateVelocity(const Vector2& NewVelocity);
	void Update(float DeltaTime);

	void Draw(SDL_Renderer* GameRenderer);


private:

	// Physics
	Vector2 Position;
	Vector2 Velocity = {0.f, 0.f};
	
	
	static constexpr float Radius = 25.f;

	// Rendering
	std::unique_ptr<Circle> ActorCircle = nullptr;
	std::unique_ptr<Rectangle> ActorRectangle = nullptr;
	SDL_FColor ActorColor = { 0.f,0.2f,1.f, 1.f};
};