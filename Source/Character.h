#pragma once
#include <memory>
#include "Actor.h"
#include "Controller.h"
#include "Vector2.h"

class Character : public Actor
{
public:
	Character();
	
	void OnPossessed(Controller* OwningContoller);
protected:
	Controller* OwningController = nullptr;
};