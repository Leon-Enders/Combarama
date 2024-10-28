#pragma once
#include <vector>
#include <functional>

class Collider;
struct SDL_Renderer;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void CheckForPossibleCollisions(float FixedDeltaTime);
	void Update(float FixedDeltaTime);
	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(Collider& ColliderToAdd);
	void RemoveCollider(Collider& ColliderToRemove);
private:


	std::vector<std::reference_wrapper<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};