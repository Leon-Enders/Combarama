#pragma once
#include <functional>
#include "../Vector2.h"


enum ActionValueType
{
	None,
	Axis1D,
	Axis2D
};



struct InputActionValue
{
	InputActionValue(){}
	InputActionValue(const InputActionValue& Other)
	{
		ActionValue = Other.ActionValue;
		ValueType = Other.ValueType;
	}

	InputActionValue& operator=(const InputActionValue& Other)
	{
		if (this == &Other) return *this;
		ActionValue = Other.ActionValue;
		ValueType = Other.ValueType;

		return *this;
	}

	Vector2 ActionValue = { 0.f,0.f };
	ActionValueType ValueType = ActionValueType::None;
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