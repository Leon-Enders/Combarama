#pragma once
#include "SDL3/SDL_rect.h"
#include "../Math/Vector2.h"
#include "../Event/Delegate.h"

struct SDL_Renderer;
class Actor;


class Collider : public std::enable_shared_from_this<Collider>
{
public:
	Collider(std::shared_ptr<Actor> InOwningActor,float InWidth, float InHeight);

	void Initialize();
	void FixedUpdate(float FixedDeltaTime);
	void Draw(SDL_Renderer* Renderer);


	void HandleCollision(std::shared_ptr<Collider> Other, const SDL_FRect& Intersection);
	

	Vector2 GetPosition()const { return { ColliderBox.x, ColliderBox.y }; }
	Vector2 GetOffset() { return CenterOffset; }

	bool DrawDebug = true;

	const SDL_FRect& GetColliderBox()const { return ColliderBox; }

	std::weak_ptr<Actor> GetOwningActor()const { return OwningActor; }
public:
	Delegate<void,std::weak_ptr<Collider>> OnOverlapBeginDelegate;

private:
	std::weak_ptr<Actor> OwningActor;

	Vector2 CenterOffset = {};
	Vector2 BoxDimensions = {};
	SDL_FRect ColliderBox;
};