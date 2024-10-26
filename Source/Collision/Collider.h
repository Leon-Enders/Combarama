#pragma once
#include <functional>
#include "SDL3/SDL_rect.h"
#include "../Math/Vector2.h"
#include "../Utility/CollisionHelper.h"

struct SDL_Renderer;
class Actor;


class Collider
{
public:
	Collider(Actor* InOwningActor,const Vector2& Origin, float InWidth, float InHeight);
	~Collider();
	void UpdatePosition(const Vector2& NewPosition);
	void Draw(SDL_Renderer* Renderer);


	void HandleCollision(const Collider& Other,const SDL_FRect& OtherBox, const SDL_FRect& Intersection);
	

	Vector2 GetPosition()const { return { ColliderBox.x, ColliderBox.y }; }
	Vector2 GetOffset() { return CenterOffset; }

	bool DrawDebug = true;

	const SDL_FRect& GetColliderBox()const { return ColliderBox; }


public:
	std::function<void(const Collider&, const ECollisionFlags)> OnCollisionEnterDelegate;
	std::function<void(const Collider&)> OnCollisionExitDelegate;
	std::function<void(const Vector2&)> OnBlockDelegate;

private:
	void OnCollisionExit(const Collider& Other);

	

	Actor* OwningActor = nullptr;

	Vector2 CenterOffset = {};
	Vector2 BoxDimensions = {};
	SDL_FRect ColliderBox;
};