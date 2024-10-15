#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "Vector2.h"
#include "Avatar.h"

class Actor
{

public:
	Actor(const Vector2& InPosition);

	void Update(float DeltaTime);

	void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor);

	void Draw(SDL_Renderer* GameRenderer);

protected:
	virtual void Initialize();

	void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	Vector2 Position;
	float Rotation = 0.f;
	Vector2 Velocity = { 0.f, 0.f };

	float Speed = 0.5f;

	
	std::unique_ptr<Avatar> ActorAvatar = nullptr;
};