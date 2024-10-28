#pragma once
#include <memory>
#include "Actor.h"
#include "../Controller/Controller.h"
#include "../Render/RenderComponent.h"
#include "../Collision/Collider.h"



//TODO: Create overload for OwningController for PlayerController
class Character : public Actor
{
public:
	Character(World* GameWorld);
	Character(World* GameWorld, const Transform& InTransform);

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	void OnPossessed(Controller* OwningContoller);

	const Vector2& GetOldPosition()const { return OldPosition; }
	const Vector2& GetVelocity()const { return Velocity; }

protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	//Collision
	virtual void OnCollisionEnter(const Collider& Other);
	virtual void OnCollisionExit(const Collider& Other);

protected:
	float Speed = 250.f;
	Vector2 Velocity = { 0.f, 0.f };
	Vector2 OldPosition;

	Controller* OwningController = nullptr;
	std::unique_ptr<RenderComponent> CharacterRenderComponent = nullptr;
	std::unique_ptr<Collider> CharacterCollider = nullptr;
};