#pragma once
#include "Vector2.h"


struct Transform
{
	Transform()
		:Position(0.f,0.f), Rotation(0.f), Scale(0.f,0.f){}

	Transform(const Vector2& InPosition, float InRotation, const Vector2& InScale)
		:Position(InPosition),Rotation(InRotation),Scale(InScale){}

	Transform(const Transform& Other)
	{
		Position = Other.Position;
		Rotation = Other.Rotation;
		Scale = Other.Scale;
	}

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
};