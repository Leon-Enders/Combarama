#pragma once
#include <memory>
#include "../Math/Vector2.h"
#include "../Render/Avatar.h"

class RenderComponent;

//TODO: Actor should not have an avatar per se, because avatar is a base shape for a character, I can create another primitive shape as a base for actor or even none
class Actor
{

public:
	Actor(const Vector2& InPosition);
	virtual void Initialize();
	void Update(float DeltaTime);

	void SetColor(const SDL_FColor& BodyColor, const SDL_FColor& HeadColor);

	const Vector2 GetPosition()const { return Position; }

protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	Vector2 Position;
	float Rotation = 0.f;
	Vector2 Velocity = { 0.f, 0.f };

	float Speed = 0.5f;

	
	std::unique_ptr<Avatar> ActorAvatar = nullptr;
	RenderComponent* OwnedRenderComponent;
};