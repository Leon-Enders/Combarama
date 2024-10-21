#pragma once
#include <memory>
#include "Actor.h"
#include "../Controller/Controller.h"
#include "../Render/RenderComponent.h"

//TODO: Create overload for OwningController for PlayerController
class Character : public Actor
{
public:
	Character(const Transform& InTransform);
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	void OnPossessed(Controller* OwningContoller);

protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	Controller* OwningController = nullptr;
	std::unique_ptr<RenderComponent> CharacterRenderComponent = nullptr;

	Vector2 Velocity = { 0.f, 0.f };

	float Speed = 500.f;
};