#pragma once
#include <vector>
#include <functional>

class Collider;
struct SDL_Renderer;
struct SDL_FRect;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void CheckForPossibleCollisions(float FixedDeltaTime);
	void Update(float FixedDeltaTime);
	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(Collider& ColliderToAdd);
private:


	std::vector<std::reference_wrapper<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};