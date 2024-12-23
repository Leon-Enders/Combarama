#pragma once
#include <cmath>

class Vector2
{
public:
	Vector2()
	{}
	Vector2(float X, float Y)
		:
		X(X),
		Y(Y)
	{
	}
	Vector2(const Vector2& rhs)
		:
		Vector2(rhs.X,rhs.Y)
	{
	}

	Vector2& operator=(const Vector2& rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		return *this;
	}

	Vector2& operator+=(const Vector2& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}

	Vector2& operator-=(const Vector2& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}

	Vector2 operator+(const Vector2& rhs)const
	{
		return Vector2(*this) += rhs;
	}

	Vector2 operator-(const Vector2& rhs)const
	{
		return Vector2(*this) -= rhs;
	}

	Vector2& operator*=(const float& rhs)
	{
		X *= rhs;
		Y *= rhs;
		return *this;
	}

	Vector2& operator*=(const Vector2& rhs)
	{
		X *= rhs.X;
		Y *= rhs.Y;
		return *this;
	}

	//Scalar Product
	float operator*(const Vector2& rhs) const
	{
		return X * rhs.X + Y * rhs.Y;
	}

	//Scale with float
	Vector2 operator*(const float& rhs) const
	{
		return Vector2(*this) *= rhs;
	}

	//Scale with Vec
	Vector2 ScaleVec2(const Vector2& rhs) const
	{
		return Vector2(*this) *= rhs;
	}

	Vector2& operator/=(const float& rhs)
	{
		X /= rhs;
		Y /= rhs;
		return *this;
	}

	Vector2 operator/(const float& rhs)const
	{
		return Vector2(*this) /= rhs;
	}

	bool operator==(const Vector2& rhs) const
	{
		return X == rhs.X && Y == rhs.Y;
	}

	bool operator!=(const Vector2& rhs) const
	{
		return !(*this == rhs);
	}

	float SizeSquared() const
	{
		return X * X + Y * Y;
	}

	float Size() const
	{
		return std::sqrt(SizeSquared());
	}
	
	Vector2& Normalize()
	{
		const float Mag = Size();
		X /= Mag;
		Y /= Mag;
		return *this;
	}
	Vector2	GetNormalized() const
	{
		Vector2 Normalized = *this;
		if (Normalized != Vector2::Zero())
		{
			Normalized.Normalize();
		}
		return Normalized;
	}

	float LookAtRotation(const Vector2& Target)const
	{
		Vector2 DeltaPosition = *this - Target;
		return std::atan2f(DeltaPosition.Y, DeltaPosition.X);
	}

	Vector2 DirectionToTarget(const Vector2& Target) const
	{
		Vector2 DeltaPosition = Target - *this;
		return DeltaPosition.Normalize();
	}

	Vector2& Rotate(const float Theta)
	{
		float cosTheta = std::cos(Theta);
		float sinTheta = std::sin(Theta);
		 
		const float NewX = X * cosTheta - Y * sinTheta;
		Y = X * sinTheta + Y * cosTheta;
		X = NewX;

		return *this;
	}

	static Vector2 Up()
	{
		return Vector2(0.f, -1.f);
	}

	static Vector2 Zero()
	{
		return Vector2(0.f, 0.f);
	}

public:
	float X = 0.f;
	float Y = 0.f;
};