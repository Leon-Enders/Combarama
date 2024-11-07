#pragma once
#include <vector>
#include <memory>

class Collider;
class Actor;
struct SDL_Renderer;
struct Vector2;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void CheckForPossibleCollisions(float FixedDeltaTime);
	void Update(float FixedDeltaTime);
	void Draw(SDL_Renderer* GameRenderer);

	void AddCollider(std::shared_ptr<Collider> ColliderToAdd);


	std::vector<Collider> GetColliderInCone(Actor* Instigator, const Vector2& Direction, float Height, float Angle);

private:


	std::vector<std::weak_ptr<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};