#pragma once
#include "CoordinateTransformer.h"
#include "../Math/Transform.h"


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


	const Transform& GetTransform()const { return CamTransform; }


	void Draw(std::vector<SDL_Vertex> Model)
	{

		for (auto& v : Model)
		{
			v.position.x *= -1;
			v.position.y *= -1;


			v.position.x *= CamTransform.Scale.X;
			v.position.y *= CamTransform.Scale.Y;

			v.position.x += CamTransform.Position.X;
			v.position.y += CamTransform.Position.Y;

			

		}
		WorldCoordinateTransformer.Draw(Model);
	}


private:
	Transform CamTransform;
	CoordinateTransformer& WorldCoordinateTransformer;
};