#pragma once
#include <numbers>
#include "Vector2.h"


class ComboramaMath
{
public:
	static float Lerp(float a, float b, float t)
	{
		return (1 - t) * a + t * b;
	}

	static bool FIsSame(float a, float b,float Tolerance = 0.0001f)
	{
		return std::fabs(a - b) < Tolerance;
	}

    static float NormalizeAngle(float Angle)
    {
        
        while (Angle < -std::numbers::pi_v<float>)
        {
            Angle += 2.0f * std::numbers::pi_v<float>;
        }
        while (Angle > std::numbers::pi_v<float>)
        {
            Angle -= 2.0f * std::numbers::pi_v<float>;
        }
        return Angle;
    }


    static float Slerpf(float Start, float End, float T)
    {
        
        float Delta = std::fmod(End - Start, 2.0f * std::numbers::pi_v<float>);
        if (Delta < -std::numbers::pi_v<float>)
        {
            Delta += 2.0f * std::numbers::pi_v<float>;
        }
        else if (Delta > std::numbers::pi_v<float>)
        {
            Delta -= 2.0f * std::numbers::pi_v<float>;
        }

        float Result = Start + Delta * T;
        return NormalizeAngle(Result);
    }

    static float Clamp(float Value, float MinVal, float MaxVal)
    {
        if (Value < MinVal)
            return MinVal;
        else if (Value > MaxVal)
            return MaxVal;
        else
            return Value;
    }
};