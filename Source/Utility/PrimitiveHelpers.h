#pragma once
#include <SDL3/SDL_render.h>
#include <cmath>
#include <vector>
#include "../Math/Vector2.h"
#include "MathConstants.h"

class  PrimitiveShape
{
protected:

	virtual void GetVerts(std::vector<SDL_Vertex>& OutTriangles) = 0;
	virtual void Triangulate() = 0;
};


class Circle : public PrimitiveShape
{
public:
	Circle(float InRadius, SDL_Vertex InCenter)
		:
		Radius(InRadius),
		Center(InCenter)
	{
	};


	void GetVerts(std::vector<SDL_Vertex>& OutTriangles) override
	{
		if (Segments <= 0) return;

		// Generate Verts for Circle Properties
		float AngleStep = 360 / Segments;
		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = static_cast<float>(AngleStep * i * (M_PI / 180.f));


			Vertices[i].position.x = Center.position.x + Radius * cos(CurrentAngle);
			Vertices[i].position.y = Center.position.y + Radius * sin(CurrentAngle);
		}

		// Triangulate Circle Verts
		Triangulate();
		
		// Populate OutTriangles with triangulated Circle Verts
		for (auto& Vert : Triangles)
		{
			Vert.color = DefaultColor;
			OutTriangles.push_back(Vert);
		}
	}

	void Triangulate() override
	{
		for (int i = 0; i < Segments; i++)
		{
			Triangles[i * 3] = Center;
			Triangles[i * 3 + 1] = Vertices[i];
			Triangles[i * 3 + 2] = Vertices[(i + 1) % Segments];
		}
	}

	static constexpr int GetNumberOfVerts() { return TriangleVerts; }

private:

	float Radius = 0;
	SDL_Vertex Center;
	SDL_FColor DefaultColor = {1.f,1.f,1.f,1.f};

	static constexpr int Segments = 120;
	static constexpr int TriangleVerts = Segments * 3;

	SDL_Vertex Vertices[Segments] = {};
	SDL_Vertex Triangles[TriangleVerts] = {};
};

class Rectangle : public PrimitiveShape
{
public:
	Rectangle(SDL_Vertex InCenter,float InWidth, float InHeight)
		:
		Center(InCenter),
		Width(InWidth),
		Height(InHeight)
	{
	};


	virtual void GetVerts(std::vector<SDL_Vertex>& OutTriangles) override
	{
		//Generate Verts for Rectangle

		float HalfWidth = Width / 2;
		float HalfHeight = Height / 2;
		
		Vertices[0].position.x = Center.position.x - HalfWidth;
		Vertices[0].position.y = Center.position.y + HalfHeight;

		Vertices[1].position.x = Center.position.x + HalfWidth;
		Vertices[1].position.y = Center.position.y + HalfHeight;

		Vertices[2].position.x = Center.position.x - HalfWidth;
		Vertices[2].position.y = Center.position.y - HalfHeight;

		Vertices[3].position.x = Center.position.x + HalfWidth;
		Vertices[3].position.y = Center.position.y - HalfHeight;


		//Triangulate Rectangle Verts
		Triangulate();


		//Populate OutTriangles with triangulated Rectangle Verts
		for (auto& Vert : Triangles)
		{
			Vert.color = DefaultColor;
			OutTriangles.push_back(Vert);
		}

	}

	virtual void Triangulate() override
	{
		Triangles[0] = Vertices[0];
		Triangles[1] = Vertices[1];
		Triangles[2] = Vertices[2];
		Triangles[3] = Vertices[3];
		Triangles[4] = Vertices[2];
		Triangles[5] = Vertices[1];
		
	}

	static constexpr int GetNumberOfVerts(){ return TriangleVerts; }
	

private:
	float Width;
	float Height;

	SDL_FColor DefaultColor = { 1.f,1.f,1.f,1.f };

	SDL_Vertex Center;
	static constexpr int VertNum = 4;
	static constexpr int TriangleVerts = 6;
	SDL_Vertex Vertices[VertNum] = {};
	SDL_Vertex Triangles[TriangleVerts] = {};
};