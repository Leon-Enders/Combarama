#pragma once
#include "Vector2.h"


struct Transform
{
	Transform()
		:Position(0.f,0.f), Rotation(0.f), Scale(1.f,1.f){}

	Transform(const Vector2& InPosition, float InRotation, const Vector2& InScale)
		:Position(InPosition),Rotation(InRotation),Scale(InScale){}

	Transform(const Transform& Other)
	{
		Position = Other.Position;
		Rotation = Other.Rotation;
		Scale = Other.Scale;
	}

	Vector2 GetForwardVector()const
	{
		return { cos(Rotation), sin(Rotation) };
	}

	bool operator==(const Transform& Other) const
	{
		const float Epsilon = 0.0001f;
		return Position == Other.Position &&
			fabs(Rotation - Other.Rotation) < Epsilon &&
			Scale == Other.Scale;
	}

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
};