#pragma once
#include <SDL3/SDL_render.h>
#include <cmath>
#include <numbers>
#include <vector>


class DebugCircle
{
public:
	static std::vector<SDL_Vertex> Make(float Radius, size_t Segments = 120, SDL_FColor Color = { 255.f,255.f,255.f,255.f })
	{
		std::vector<SDL_Vertex> Verts = { Segments,{SDL_FPoint(), Color, SDL_FPoint()} };
		float AngleStep = static_cast<float>(360.f / Segments);

		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = (AngleStep * i * (std::numbers::pi_v<float> / 180.f));

			Verts[i].color = Color;
			Verts[i].position.x = Radius * cos(CurrentAngle);
			Verts[i].position.y = Radius * sin(CurrentAngle);
		}

		return Verts;
	}
};

class DebugRectangle
{
public:

	static std::vector<SDL_Vertex> Make(float Width, float Height, SDL_FColor Color = { 255.f,255.f,255.f,255.f })
	{
		std::vector<SDL_Vertex> Verts = { 4,{SDL_FPoint(), Color, SDL_FPoint()} };
		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;

		Verts[0].position.x -= HalfWidth;
		Verts[0].position.y += HalfHeight;

		Verts[1].position.x += HalfWidth;
		Verts[1].position.y += HalfHeight;

		Verts[2].position.x -= HalfWidth;
		Verts[2].position.y -= HalfHeight;

		Verts[3].position.x += HalfWidth;
		Verts[3].position.y -= HalfHeight;

		return Verts;
	}
};