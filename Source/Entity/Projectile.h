#pragma once
#include <memory>
#include "Actor.h"
#include "../Render/RenderComponent.h"



class Projectile : public Actor
{
public:
	Projectile(World* GameWorld);
	Projectile(World* GameWorld, const Transform& InTransform);
	virtual ~Projectile()= default;

	virtual void Initialize()override;
	virtual void Update(float DeltaTime)override;
	virtual void FixedUpdate(float FixedDeltaTime)override;

	void UpdateVelocity(const Vector2& NewVelocity);
	void SetSpeed(float NewSpeed) { ProjectileSpeed = NewSpeed; }
protected:

	void UpdatePosition(float DeltaTime);


private:

	float ProjectileSize = 30.f;
	float ProjectileSpeed = 1000.f;
	Vector2 Velocity = {};

	std::unique_ptr<RenderComponent> ProjectileRenderComponent;
};