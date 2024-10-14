#pragma once
#include "../Vector2.h"

enum E_AxisMapping
{
	Down,
	Up,
	Left,
	Right
};
enum ActionValueType
{
	None,
	Axis1D,
	Axis2D
};

;

struct InputActionValue
{
	InputActionValue() = default;

	InputActionValue(const InputActionValue& Other)
	{
		Value = Other.Value;
		ValueType = Other.ValueType;
	}

	InputActionValue& operator=(const InputActionValue& Other)
	{
		if (this != &Other)
		{
			Value = Other.Value;
			ValueType = Other.ValueType;
		}
		return *this;
	}
	void ClearValue(E_AxisMapping AxisToUpdate)
	{
		switch (AxisToUpdate)
		{
		case E_AxisMapping::Up:
			Value.Y = 0.f;
			break;
		case E_AxisMapping::Down:
			Value.Y = 0.f;
			break;
		case E_AxisMapping::Left:
			Value.X = 0.f;
			break;
		case E_AxisMapping::Right:
			Value.X = 0.f;
			break;
		default:
			break;
		}
	}

	void UpdateValue(E_AxisMapping AxisToUpdate)
	{
		//if (ValueType != ActionValueType::Axis2D) return;

		switch (AxisToUpdate)
		{
		case E_AxisMapping::Up:
			Value.Y = -1.f;
			break;
		case E_AxisMapping::Down:
			Value.Y = 1.f;
			break;
		case E_AxisMapping::Left:
			Value.X = -1.f;
			break;
		case E_AxisMapping::Right:
			Value.X = 1.f;
			break;
		default:
			break;
		}
	}

	bool IsNonZero(float Tolerance = 0.0001f) const { return Value.SizeSquared() >= Tolerance * Tolerance; };

	template<typename T>
	inline T Get() const;


	Vector2 Value = { 0.f,0.f };
	ActionValueType ValueType = ActionValueType::None;
};

template<>
inline bool InputActionValue::Get() const
{
	return IsNonZero();
}

template<>
inline float InputActionValue::Get() const
{
	return Value.X;
}

template<>
inline Vector2 InputActionValue::Get() const
{
	return Vector2(Value.X, Value.Y);
}
