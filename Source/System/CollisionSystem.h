#pragma once
#include <vector>
#include <functional>

class Collider;
struct SDL_Renderer;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void Update();
	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(Collider& ColliderToAdd);
private:


	std::vector<std::reference_wrapper<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};