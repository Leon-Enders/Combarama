#pragma once
#include <vector>

class Collider;
class SDL_Renderer;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };


	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(Collider* ColliderToAdd);
private:


	std::vector<Collider*> ActiveColliders;
	static CollisionSystem Instance;
};