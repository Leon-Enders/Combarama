#pragma once
#include <vector>
#include <memory>



class Vector2;
class Collider;
class Actor;
struct SDL_Renderer;

class CollisionSystem
{
public:
	static CollisionSystem& Get() { return Instance; };

	void CheckForPossibleCollisions(float FixedDeltaTime);
	void FixedUpdate(float FixedDeltaTime);

	void AddCollider(std::shared_ptr<Collider> ColliderToAdd);


	std::vector<Collider> GetColliderInCone(std::weak_ptr<Actor> Instigator, const Vector2& Direction, float Height, float Angle);

private:


	std::vector<std::weak_ptr<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};