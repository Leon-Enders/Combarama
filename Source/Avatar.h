#pragma once
#include "SDL3/SDL_render.h"
#include "vector"
#include "PrimitiveHelpers.h"
#include "Vector2.h"

class Avatar
{
public:
	Avatar(const Vector2& InPosition);


	void UpdatePosition(const Vector2& NewPosition)
	{
		float DeltaX = NewPosition.X - Position.X;
		float DeltaY = NewPosition.Y - Position.Y;

		Position.X = NewPosition.X;
		Position.Y = NewPosition.Y;

		for (auto& Vert : Triangles)
		{
			Vert.position.x += DeltaX;
			Vert.position.y += DeltaY;
		}
	}

	void Rotate(const Vector2& TargetPosition)
	{
		float DeltaX = Position.X - TargetPosition.X;
		float DeltaY = Position.Y - TargetPosition.Y;

		// Calculate the angle in radians
		float AngleInRad = std::atan2f(DeltaX, DeltaY);


		if (AngleInRad < 0)
		{
			AngleInRad += 2 * M_PI;
		}

		float DeltaRotation = CurrentRotation - AngleInRad;

		CurrentRotation = AngleInRad;

		float CosTheta = cos(DeltaRotation);
		float SinTheta = sin(DeltaRotation);

		for (int i = 0; i < MaxVerts; ++i)
		{
		
			float RelativeX = Triangles[i].position.x - Position.X;
			float RelativeY = Triangles[i].position.y - Position.Y;

			
			float RotatedX = RelativeX * CosTheta - RelativeY * SinTheta;
			float RotatedY = RelativeX * SinTheta + RelativeY * CosTheta;

			
			Triangles[i].position.x = RotatedX + Position.X;
			Triangles[i].position.y = RotatedY + Position.Y;
		}
	}
	void Draw(SDL_Renderer* Renderer);

private:
	
	Vector2 Position;
	float CurrentRotation = 0.f;
	static constexpr float Radius = 25.f;
	static constexpr float HeadWidth = 25.f;
	static constexpr float HeadHeight = 15.f;
	static constexpr int MaxVerts = Circle::GetVertNumber() + Rectangle::GetVertNumber();

	SDL_Vertex Triangles[MaxVerts];
	int TrianglesSize = 0;
};