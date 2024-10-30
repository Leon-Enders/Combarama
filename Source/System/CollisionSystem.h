#pragma once
#include <vector>
#include <functional>

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

	void AddCollider(Collider& ColliderToAdd);
	void RemoveCollider(Collider& ColliderToRemove);


	std::vector<Collider> GetColliderInCone(Actor* Instigator, const Vector2& Direction, float Height, float Angle);

	std::vector<Collider> GetOverlapsInSphere(Actor* Instigator, float Radius);
private:


	std::vector<std::reference_wrapper<Collider>> ActiveColliders;
	static CollisionSystem Instance;
};