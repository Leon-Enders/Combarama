#pragma once
#include <functional>
#include "SDL3/SDL_rect.h"
#include "../Math/Vector2.h"

struct SDL_Renderer;
class Actor;


class Collider
{
public:
	Collider(Actor* InOwningActor,float InWidth, float InHeight);
	~Collider();

	void FixedUpdate(float FixedDeltaTime);
	void Draw(SDL_Renderer* Renderer);


	void HandleCollision(const Collider& Other, const SDL_FRect& Intersection);
	

	Vector2 GetPosition()const { return { ColliderBox.x, ColliderBox.y }; }
	Vector2 GetOffset() { return CenterOffset; }

	bool DrawDebug = true;

	const SDL_FRect& GetColliderBox()const { return ColliderBox; }

	Actor* GetOwningActor()const { return OwningActor; }
public:
	std::function<void(const Collider&)> OnCollisionEnterDelegate;
	std::function<void(const Collider&)> OnCollisionExitDelegate;
	std::function<void(const Vector2&)> OnBlockDelegate;

private:
	void OnCollisionExit(const Collider& Other);

	Actor* OwningActor = nullptr;

	Vector2 CenterOffset = {};
	Vector2 BoxDimensions = {};
	SDL_FRect ColliderBox;
};