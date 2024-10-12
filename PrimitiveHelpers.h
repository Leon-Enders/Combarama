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
		// Populate Circle Verts for set Segments

		float AngleStep = 360 / Segments;
		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = static_cast<float>(AngleStep * i * (M_PI / 180.f));


			Vertices[i].position.x = Center.position.x + Radius * cos(CurrentAngle);
			Vertices[i].position.y = Center.position.y + Radius * sin(CurrentAngle);

			Vertices[i].color = Color;
		}

		// Triangulate Circle
		for (int i = 0; i < Segments; i++)
		{
			Triangles[i * 3] = Center;
			Triangles[i * 3 + 1] = Vertices[i];
			Triangles[i * 3 + 2] = Vertices[(i + 1) % Segments];
		}
	}


	void Draw(SDL_Renderer* Renderer)
	{
		SDL_RenderGeometry(Renderer, NULL, Triangles, TriangleVerts, NULL, 0);
	}

	void UpdatePosition(const Vector2& NewPosition)
	{
		float DeltaX = NewPosition.X - Center.position.x;
		float DeltaY = NewPosition.Y - Center.position.y;

		Center.position.x = NewPosition.X;
		Center.position.y = NewPosition.Y;

		for (auto& Vert : Triangles)
		{
			Vert.position.x += DeltaX;
			Vert.position.y += DeltaY;
		}
	}

private:

	float Radius = 0;
	SDL_Vertex Center;
	SDL_FColor Color;


	static constexpr int Segments = 120;
	static constexpr int TriangleVerts = Segments * 3;

	SDL_Vertex Vertices[Segments];
	SDL_Vertex Triangles[TriangleVerts];
};

class Rectangle
{
public:
	Rectangle(SDL_Vertex InCenter,float InWidth, float InHeight, SDL_FColor InColor)
		:
		Center(InCenter),
		Width(InWidth),
		Height(InHeight),
		Color(InColor)
	{
		Center.color = Color;
	};


	void InitializeRectangle()
	{
		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;


		Vertices[0].position.x = Center.position.x - HalfWidth;
		Vertices[0].position.y = Center.position.y + HalfHeight;
		Vertices[0].color = Color;

		Vertices[1].position.x = Center.position.x + HalfWidth;
		Vertices[1].position.y = Center.position.y + HalfHeight;
		Vertices[1].color = Color;

		Vertices[2].position.x = Center.position.x - HalfWidth;
		Vertices[2].position.y = Center.position.y - HalfHeight;
		Vertices[2].color = Color;

		Vertices[3].position.x = Center.position.x + HalfWidth;
		Vertices[3].position.y = Center.position.y - HalfHeight;
		Vertices[3].color = Color;

		
		Triangles[0] = Vertices[0];
		Triangles[1] = Vertices[1];
		Triangles[2] = Vertices[2];
		Triangles[3] = Vertices[3];
		Triangles[4] = Vertices[2];
		Triangles[5] = Vertices[1];
		
	}


	void Draw(SDL_Renderer* Renderer)
	{
		SDL_RenderGeometry(Renderer, NULL, Triangles, TriangleVerts, NULL, 0);
	}

	void UpdatePosition(const Vector2& NewPosition)
	{
		float DeltaX = NewPosition.X - Center.position.x;
		float DeltaY = NewPosition.Y - Center.position.y - 25.f;

		Center.position.x = NewPosition.X;
		Center.position.y = NewPosition.Y - 25.f;

		for (auto& Vert : Triangles)
		{
			Vert.position.x += DeltaX;
			Vert.position.y += DeltaY;
		}
	}

private:

	
	float Width;
	float Height;

	SDL_Vertex Center;
	SDL_FColor Color;


	static constexpr int VertNum = 4;
	static constexpr int TriangleVerts = 6;
	SDL_Vertex Vertices[VertNum];
	SDL_Vertex Triangles[TriangleVerts];
};