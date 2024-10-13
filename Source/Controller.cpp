#include "Controller.h"

Controller::Controller()
{
	ControllerInputComponent = std::make_unique<InputComponent>();
}
