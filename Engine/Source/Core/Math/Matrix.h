#pragma once
#include <cmath>
#include "SDL3/SDL_rect.h"
#include "Transform.h"



class TMatrix
{
public:


	//Apply Matrix To Vec2
	//Vector2 operator*(const Vector2& rhs)
	//{
	//	return {}
	//}

	//Create IdentityMatrix
	static TMatrix Identity()
	{
		return {
			1.f,0.f,1.f,
			0.f,1.f,1.f,
			0.f,0.f,0.f
		};
	}

	//Create ScaleMatrix
	static TMatrix Scale(const Vector2& Scale)
	{
		// Use ApplyMatrix to Vec2 here, and simply Use Identity scaled by the scale
		return {
			1.f*Scale.X,0.f*Scale.X,1.f,
			0.f*Scale.Y,1.f*Scale.Y,1.f,
			0.f,0.f,0.f
		};
	}

	//Create RotationMatrix
	//Create TranslationMatrix

	float Matrix[3][3] = {0};
};