#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"
#include "Avatar.h"
#include "Input/InputComponent.h"


class Actor
{

public:
	Actor(const Vector2& InPosition);
	~Actor() = default;


	void AddInput(const SDL_Event& InputEvent);
	void HandleInput();

	void UpdateVelocity(const Vector2& NewVelocity);
	void Update(float DeltaTime);

	void Draw(SDL_Renderer* GameRenderer);


private:

	// Physics
	Vector2 Position;
	Vector2 Velocity = {0.f, 0.f};

	// Rendering
	std::unique_ptr<Avatar> ActorAvatar = nullptr;


	//// TODO: only the player needs an InputComponent, this should also be put into a controller class
	std::unique_ptr<InputComponent> ActorInputComponent = nullptr;
};