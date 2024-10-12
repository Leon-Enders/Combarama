#pragma once
#include <SDL3/SDL_render.h>
#include <cmath>

class Circle
{
public:
	Circle() {};


	void InitializeCircle()
	{
		// Populate Circle Verts for given segments

		float AngleStep = 360 / segments;
		for (int i = 0; i < segments; i++)
		{
			float CurrentAngle = AngleStep * i;

			SDL_FPoint NewVertexPoint = { std::cos(CurrentAngle) * Radius + Center.x, std::sin(CurrentAngle) * Radius + Center.y};
			Vertices[i].position = NewVertexPoint;
			Vertices[i].color = CircleColor;
		}

		int TriangleCounter = 0;
		// Triangulate Circle
		for (int i = 0; i < segments * 3; i++)
		{

			// Blank VertexPoint
			SDL_FPoint NewVertexPoint;

			// Add Correct Vertice to TriangleVertices
			switch (TriangleCounter)
			{
			case 0:
				NewVertexPoint = Center;
				break;
			case 1:
				NewVertexPoint = Vertices[i - 2].position;
				break;
			case 2:
				NewVertexPoint = Vertices[i - 1].position;
				break;
			}
			
			TriangleCounter++;
			if (TriangleCounter >= 3)
			{
				TriangleCounter = 0;
			}

			Triangles[i].position = NewVertexPoint;
			Triangles[i].color = CircleColor;
		}
	}


	void Draw(SDL_Renderer* Renderer, SDL_Window* Window)
	{
		SDL_RenderGeometry(Renderer, NULL, Triangles, segments * 3, NULL, 0);
	}

private:

	SDL_FPoint Center = { 255, 255 };
	int Radius = 64;


	static constexpr int segments = 120;
	static constexpr SDL_FColor CircleColor = { 1.f, 0.f, 0.f, 1.f };

	SDL_Vertex Vertices[segments];
	SDL_Vertex Triangles[segments * 3];
};