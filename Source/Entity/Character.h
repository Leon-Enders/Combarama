#pragma once
#include <memory>
#include "Actor.h"
#include "../Controller/Controller.h"
#include "../Render/RenderComponent.h"
#include "../Collision/Collider.h"


class Collider;
//TODO: Create overload for OwningController for PlayerController
class Character : public Actor
{
public:
	Character(World* GameWorld);
	Character(World* GameWorld, const Transform& InTransform);
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	void OnPossessed(Controller* OwningContoller);

	const Vector2& GetVecolity()const { return Velocity; }
	void SetCanMove(bool NewCanMove) 
	{
		CanMove = NewCanMove; 
	}
protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	float Speed = 500.f;
	Vector2 Velocity = { 0.f, 0.f };
	

	Controller* OwningController = nullptr;
	std::unique_ptr<RenderComponent> CharacterRenderComponent = nullptr;

	std::unique_ptr<Collider> CharacterCollider = nullptr;

private:
	bool CanMove = true;
};