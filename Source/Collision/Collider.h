#pragma once
#include <functional>
#include "SDL3/SDL_rect.h"
#include "BoundingBox.h"
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


	void HandleCollisionBounding(const Collider& Other);
	void HandleCollision(const Collider& Other, const SDL_FRect& Intersection);

	void SetIsActive(bool InIsActive) { IsActive = InIsActive; }

	inline Vector2 GetPosition()const { return { ColliderBox.x, ColliderBox.y }; }
	inline Vector2 GetOffset()const { return CenterOffset; }
	inline const SDL_FRect& GetColliderBox()const { return ColliderBox; }
	inline const bool GetIsActive() const { return IsActive; }


public:
	bool DrawDebug = true;
	bool IsActive = true;

	std::function<void(const Collider&)> OnCollisionEnterDelegate;
	std::function<void(const Collider&)> OnCollisionExitDelegate;
	std::function<void(const Vector2&)> OnBlockDelegate;

private:
	void OnCollisionExit(const Collider& Other);

	Actor* OwningActor = nullptr;

	Vector2 CenterOffset = {};
	Vector2 BoxDimensions = {};
	SDL_FRect ColliderBox;
	BoundingBox BoundingBo;
};