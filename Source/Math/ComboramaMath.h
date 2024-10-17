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
	};


    static float Slerpf(float Start, float End, float T) {
        
        float Delta = std::fmod(End - Start, 2.0f * M_PI);
        if (Delta < -M_PI) {
            Delta += 2.0f * M_PI;
        }
        else if (Delta > M_PI) {
            Delta -= 2.0f * M_PI;
        }

        return Start + Delta * T;
    }
};