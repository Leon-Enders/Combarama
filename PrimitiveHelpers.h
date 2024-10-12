#pragma once
#include <SDL3/SDL_render.h>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>




class Circle
{
public:
	Circle(float InRadius, SDL_Vertex InCenter, SDL_FColor InColor)
		:
		Radius(InRadius),
		Center(InCenter),
		Color(InColor)
	{
		Center.color = Color;
	};


	void InitializeCircle()
	{
		// Populate Circle Verts for set segments

		float AngleStep = 360 / segments;
		for (int i = 0; i < segments; i++)
		{
			float CurrentAngle = AngleStep * i * (M_PI / 180.f);


			Vertices[i].position.x = Center.position.x + Radius * cos(CurrentAngle);
			Vertices[i].position.y = Center.position.y + Radius * sin(CurrentAngle);

			Vertices[i].color = Color;
		}

		// Triangulate Circle
		for (int i = 0; i < segments; i++)
		{
			Triangles[i * 3] = Center;
			Triangles[i * 3 + 1] = Vertices[i];
			Triangles[i * 3 + 2] = Vertices[(i + 1) % segments];
		}
	}


	void Draw(SDL_Renderer* Renderer)
	{
		SDL_RenderGeometry(Renderer, NULL, Triangles, segments * 3, NULL, 0);
	}

	void UpdatePosition(const Vector2& NewPosition)
	{
		Center.position.x = NewPosition.X;
		Center.position.y = NewPosition.Y;

		InitializeCircle();
	}

private:

	int Radius = 0;
	SDL_Vertex Center;
	SDL_FColor Color;


	static constexpr int segments = 120;

	SDL_Vertex Vertices[segments];
	SDL_Vertex Triangles[segments * 3];
};