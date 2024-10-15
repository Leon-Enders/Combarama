#pragma once
#include <memory>
#include "Actor.h"
#include "Controller.h"

class Character : public Actor
{
public:
	Character(const Vector2& InPosition);
	
	void OnPossessed(Controller* OwningContoller);
protected:
	virtual void Initialize() override;

	
	Controller* OwningController = nullptr;
};