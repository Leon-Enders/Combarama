#pragma once
#include <memory>
#include "Input/InputComponent.h"

class Controller
{
public:
	Controller();


private:

	std::unique_ptr<InputComponent> ControllerInputComponent ;
};