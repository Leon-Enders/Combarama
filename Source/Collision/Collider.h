#pragma once
#include "../Math/Vector2.h"
#include "SDL3/SDL_rect.h"

struct SDL_Renderer;

class Collider
{
public:
	Collider(const Vector2& Origin, float InWidth, float InHeight);
	~Collider();
	void UpdatePosition(const Vector2& NewPosition);
	void Draw(SDL_Renderer* Renderer);

	void OnCollisionEnter(const Collider* Other);


	bool DrawDebug = true;

	const SDL_FRect* GetColliderBox()const { return &ColliderBox; }
private:

	// since FRects have their center on the upper left corner
	// we have to make some calculations to convert rectangle position
	// so that it centers with the origin
	
	Vector2 CenterOffset = {};
	SDL_FRect ColliderBox;
};