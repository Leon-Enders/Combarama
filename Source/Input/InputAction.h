#pragma once
#include <functional>

class InputAction
{
public:
	InputAction(const std::function<void()>& ActionDelegate)
		:
		InputActionDelegate(ActionDelegate)
	{

	}

	void Execute()
	{
		if (InputActionDelegate)
		{
			InputActionDelegate();
		}
	}

private:
	std::function<void()> InputActionDelegate;
};