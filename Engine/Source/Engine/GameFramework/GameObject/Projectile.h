#pragma once
#include <memory>
#include "Actor.h"
#include "../../Physics/Collider.h"



class Projectile : public Actor, public std::enable_shared_from_this<Projectile>
{
public:
	Projectile(World* GameWorld, const Transform& InTransform);
	virtual ~Projectile()= default;

	virtual void Initialize()override;
	virtual void Update(float DeltaTime)override;
	virtual void FixedUpdate(float FixedDeltaTime)override;

	void UpdateVelocity(const Vector2& NewVelocity);
	void SetSpeed(float NewSpeed) { ProjectileSpeed = NewSpeed; }

protected:
	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider) override;


	void UpdatePosition(float DeltaTime);
	
private:

	float LifeTime = 1.f;
	float ProjectileSize = 15.f;
	float ProjectileSpeed = 1000.f;
	int ProjectileDamage = 2;
	Vector2 Velocity = {};

	PrimitiveComponent* ProjectilePrimitive = nullptr;
	std::shared_ptr<Collider> ProjectileCollider;
};