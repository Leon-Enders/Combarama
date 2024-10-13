#pragma once
#include <vector>
#include "InputComponent.h"

//TODO This class gets initialized when the game starts and handles Processing Input and delegating it to all InputComponents registered
class InputSystem
{
public:
	InputSystem(){}

private:
	std::vector<InputComponent> InputComponents;
};