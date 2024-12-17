#pragma once
#include <SDL3/SDL_rect.h>
#include <cmath>
#include <numbers>
#include <vector>


class DebugCircle
{
public:
	static std::vector<SDL_FPoint> Make(float Radius, size_t Segments = 120)
	{
		std::vector<SDL_FPoint> Points = { Segments+1,SDL_FPoint() };
		float AngleStep = static_cast<float>(360.f / Segments);

		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = (AngleStep * i * (std::numbers::pi_v<float> / 180.f));

			Points[i].x = Radius * cos(CurrentAngle);
			Points[i].y = Radius * sin(CurrentAngle);
		}
		Points[Segments] = Points[0];

		return Points;
	}
};

class DebugRect
{
public:

	static std::vector<SDL_FPoint> Make(float HalfExtentX, float HalfExtentY)
	{
		std::vector<SDL_FPoint> Points(5, SDL_FPoint());

		Points[0].x = -HalfExtentX;
		Points[0].y = HalfExtentY;

		Points[1].x = HalfExtentX;
		Points[1].y = HalfExtentY;

		Points[2].x = HalfExtentX;
		Points[2].y = -HalfExtentY;

		Points[3].x = -HalfExtentX;
		Points[3].y = -HalfExtentY;

		Points[4] = Points[0];

		return Points;
	}
};