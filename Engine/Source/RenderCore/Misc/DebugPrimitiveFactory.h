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
		std::vector<SDL_FPoint> Points = { Segments,SDL_FPoint() };
		float AngleStep = static_cast<float>(360.f / Segments);

		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = (AngleStep * i * (std::numbers::pi_v<float> / 180.f));

			Points[i].x = Radius * cos(CurrentAngle);
			Points[i].y = Radius * sin(CurrentAngle);
		}

		return Points;
	}
};

class DebugRectangle
{
public:

	static std::vector<SDL_FPoint> Make(float Width, float Height)
	{
		std::vector<SDL_FPoint> Points = { 4,SDL_FPoint() };
		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;

		Points[0].x -= HalfWidth;
		Points[0].y += HalfHeight;

		Points[1].x += HalfWidth;
		Points[1].y += HalfHeight;

		Points[2].x -= HalfWidth;
		Points[2].y -= HalfHeight;

		Points[3].x += HalfWidth;
		Points[3].y -= HalfHeight;

		return Points;
	}
};