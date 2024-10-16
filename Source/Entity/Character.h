#pragma once
#include <memory>
#include "Actor.h"
#include "../Controller/Controller.h"

//TODO: Create overload for OwningController for PlayerController
class Character : public Actor
{
public:
	Character(const Vector2& InPosition);
	virtual void Initialize() override;

	void OnPossessed(Controller* OwningContoller);

protected:

	Controller* OwningController = nullptr;
};