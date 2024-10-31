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


	bool operator==(const Vector2& Other) const
	{
		const float Epsilon = 0.0001f;
		return (fabs(X - Other.X) < Epsilon) &&
			(fabs(Y - Other.Y) < Epsilon);
	}
	
	Vector2& operator+=(const Vector2& Other)
	{
		X += Other.X;
		Y += Other.Y;

		return *this;
	}

	friend Vector2 operator+(const Vector2& A, const Vector2& B)
	{
		return Vector2(A.X + B.X, A.Y + B.Y);
	}

	friend Vector2 operator-(const Vector2& A, const Vector2& B)
	{
		return Vector2(A.X - B.X, A.Y - B.Y);
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

	float Size() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	float SizeSquared() const
	{
		return X * X + Y * Y;
	}

	
	Vector2 Normalize() const
	{
		float Mag = Size();

		if (Mag > 0.0f)
		{
			return Vector2(X / Mag, Y / Mag);
		}

		return Vector2(0, 0);
	}

	float Dot(const Vector2& other) const
	{
		return X * other.X + Y * other.Y;
	}

	static Vector2 UP()
	{
		return Vector2(0.f, -1.f);
	}

	static Vector2 Zero()
	{
		return Vector2(0.f, 0.f);
	}
	float X =0;
	float Y =0;
};