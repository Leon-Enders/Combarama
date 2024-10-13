#pragma once
#include <memory>
#include "Input/InputComponent.h"

//TODO: This class creates InputActions and an InputActionContext
class Controller
{
public:
	Controller();


private:

	std::unique_ptr<InputComponent> ControllerInputComponent ;
};