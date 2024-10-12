#pragma once
#include <cmath>

struct Vector2
{
	Vector2(){}

	Vector2(float InX, float InY)
	{
		X = InX;
		Y = InY;
	}
	Vector2(const Vector2& Other)
	{
		X = Other.X;
		Y = Other.Y;
	}

	Vector2& operator=(const Vector2& Other)
	{
		if (this == &Other) return *this;

		X = Other.X;
		Y = Other.Y;

		return *this;
	}

	Vector2(int InX, int InY) : X(static_cast<float>(InX)), Y(static_cast<float>(InY)) {}

	~Vector2() = default;


	bool operator==(const Vector2& Other)
	{
		return X == Other.X && Y == Other.Y;
	}

	Vector2& operator+=(const Vector2& Other)
	{
		X += Other.X;
		Y += Other.Y;

		return *this;
	}

	Vector2& operator-=(const Vector2& Other)
	{
		X -= Other.X;
		Y -= Other.Y;

		return *this;
	}

	Vector2& operator*=(const float Scale)
	{
		X *= Scale;
		Y *= Scale;
		return *this;
	}

	Vector2 operator*(const float Scale) const
	{
		return Vector2(X * Scale, Y * Scale);
	}

	float Magnitude() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	
	Vector2 Normalize() const
	{
		float Mag = Magnitude();

		if (Mag > 0.0f)
		{
			return Vector2(X / Mag, Y / Mag);
		}

		return Vector2(0, 0);
	}


	float X =0;
	float Y =0;
};