#pragma once
#include <functional>
#include "InputActionValue.h"



class InputAction
{

public:
	
	InputAction() = default;

	void SetActionValue(const InputActionValue& InActionValue)
	{
		ActionValue = InActionValue;
	}

	
	void BindFunction(const std::function<void(const InputActionValue&)>& ActionDelegate)
	{
		InputActionDelegate = ActionDelegate;
	}
	
	void Execute()
	{
		if (InputActionDelegate)
		{
			InputActionDelegate(ActionValue);
		}
	}
	inline const InputActionValue& GetActionValue()const { return ActionValue; }

private:
	
	std::function<void(const InputActionValue&)> InputActionDelegate = nullptr;

	InputActionValue ActionValue;
};