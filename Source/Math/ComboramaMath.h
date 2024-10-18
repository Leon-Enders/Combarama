#pragma once
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
        
        while (Angle < -static_cast<float>(M_PI))
        {
            Angle += 2.0f * static_cast<float>(M_PI);
        }
        while (Angle > static_cast<float>(M_PI))
        {
            Angle -= 2.0f * static_cast<float>(M_PI);
        }
        return Angle;
    }


    static float Slerpf(float Start, float End, float T)
    {
        
        float Delta = static_cast<float>(std::fmod(End - Start, 2.0f * M_PI));
        if (Delta < -static_cast<float>(M_PI))
        {
            Delta += 2.0f * static_cast<float>(M_PI);
        }
        else if (Delta > static_cast<float>(M_PI))
        {
            Delta -= 2.0f * static_cast<float>(M_PI);
        }

        float Result = Start + Delta * T;
        return NormalizeAngle(Result);
    }
};