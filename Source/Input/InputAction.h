#pragma once
#include <functional>
#include "../Vector2.h"


enum ActionValueType
{
	None,
	Vector
};



class InputAction
{

public:
	
	InputAction(ActionValueType Type = ActionValueType::None)
		: 
	ValueType(Type)
	{

	}


	template<typename T>
	void BindFunction(const std::function<void(T)>& ActionDelegate)
	{
		InputActionDelegate = [ActionDelegate](void* value)
			{
				ActionDelegate(*static_cast<T*>(value)); 
			};
	}

	
	void BindFunction(const std::function<void(void*)>& ActionDelegate)
	{
		InputActionDelegate = ActionDelegate;
	}
	
	void Execute(Vector2 InputVector)
	{
		if (InputActionDelegate && ValueType == ActionValueType::Vector)
		{
			InputActionDelegate(static_cast<void*>(&InputVector));
		}
	}
	
	void Execute()
	{
		if (InputActionDelegate)
		{
			InputActionDelegate(nullptr);
		}
	}

	inline const ActionValueType GetActionValue()const { return ValueType; }

private:
	
	std::function<void(void*)> InputActionDelegate = nullptr;

	ActionValueType ValueType = ActionValueType::None;
};