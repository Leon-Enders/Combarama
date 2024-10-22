#pragma once
#include <vector>

class Collider;
struct SDL_Renderer;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void Update();
	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(Collider* ColliderToAdd);
private:


	std::vector<Collider*> ActiveColliders;
	static CollisionSystem Instance;
};