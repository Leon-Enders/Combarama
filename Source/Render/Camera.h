#pragma once
#include "CoordinateTransformer.h"
#include "../Math/Transform.h"
#include "Drawable.h"

class Camera
{
public:
	Camera(CoordinateTransformer& WorldCoordinateTransformer)
		:
		WorldCoordinateTransformer(WorldCoordinateTransformer)
	{

	}


	void SetPosition(const Vector2& NewPosition)
	{
		CamTransform.Position = NewPosition;
	}

	void Translate(const Vector2& PositionToAdd)
	{
		CamTransform.Position += PositionToAdd;
	}

	void SetScale(const Vector2& NewScale)
	{
		CamTransform.Scale = NewScale;
	}

	void Scale(float Scale)
	{
		CamTransform.Scale *= Scale;
	}

	void SetRotation(const float NewRotation)
	{
		CamTransform.Rotation = NewRotation;
	}

	void Rotate(const float RotationToAdd)
	{
		CamTransform.Rotation += RotationToAdd;
	}


	void Draw(Drawable& InDrawable)const
	{
		InDrawable.Translate(CamTransform.Position * -1.f);
		InDrawable.Scale(CamTransform.Scale);
		WorldCoordinateTransformer.Draw(InDrawable);
	}

	const Transform& GetTransform()const { return CamTransform; }


private:
	Transform CamTransform;
	CoordinateTransformer& WorldCoordinateTransformer;
};