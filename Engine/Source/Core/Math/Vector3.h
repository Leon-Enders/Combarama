#pragma once
#include "Vector2.h"


// Vector3 class for storing 2D Translation into a 3x3 Matrix

class Vector3
{
public:
	Vector3()
	{}
	Vector3(float X, float Y)
		:
		X(X),
		Y(Y)
	{
	}
	Vector3(const Vector3& rhs)
		:
		Vector3(rhs.X, rhs.Y)
	{
	}

	//Convert Vec3 to Vec2
	explicit Vector3(const Vector2& Vec2)
		:
		Vector3(Vec2.X, Vec2.Y)
	{}
	//Convert Vec2 to Vec3
	explicit operator Vector2() const
	{
		return { X,Y };
	}

	Vector3& operator=(const Vector3& rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		W = rhs.W;
		return *this;
	}

	Vector3& operator+=(const Vector3& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}

	Vector3& operator-=(const Vector3& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}

	Vector3 operator+(const Vector3& rhs)const
	{
		return Vector3(*this) += rhs;
	}

	Vector3 operator-(const Vector3& rhs)const
	{
		return Vector3(*this) -= rhs;
	}

	Vector3 operator-()const
	{
		return Vector3(-X, -Y);
	}

	Vector3& operator*=(const float& rhs)
	{
		X *= rhs;
		Y *= rhs;
		return *this;
	}

	Vector3& operator*=(const Vector3& rhs)
	{
		X *= rhs.X;
		Y *= rhs.Y;
		return *this;
	}

	//Scalar Product
	float operator*(const Vector3& rhs) const
	{
		return X * rhs.X + Y * rhs.Y;
	}

	//Scale with float
	Vector3 operator*(const float& rhs) const
	{
		return Vector3(*this) *= rhs;
	}

	//Scale with Vec
	Vector3 ScaleVec2(const Vector3& rhs) const
	{
		return Vector3(*this) *= rhs;
	}

	Vector3& operator/=(const float& rhs)
	{
		X /= rhs;
		Y /= rhs;
		return *this;
	}

	Vector3 operator/(const float& rhs)const
	{
		return Vector3(*this) /= rhs;
	}

	bool operator==(const Vector3& rhs) const
	{
		return X == rhs.X && Y == rhs.Y;
	}

	bool operator!=(const Vector3& rhs) const
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

	Vector3& Normalize()
	{
		const float Mag = Size();
		X /= Mag;
		Y /= Mag;
		return *this;
	}
	Vector3	GetNormalized() const
	{
		Vector3 Normalized = *this;
		Normalized.Normalize();
		return Normalized;
	}

public:
	float X = 0.f;
	float Y = 0.f;
	float W = 1.f;
};