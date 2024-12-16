#pragma once
#include <SDL3/SDL_render.h>
#include <cmath>
#include <numbers>
#include <vector>
#include "../../Core/Math/Transform.h"
#include "../../Core/Math/Matrix.h"


class Circle
{
public:
	Circle()
	{
	};


	static std::vector<SDL_Vertex> Make(float Radius, const Transform& PivotTransform = Transform(), size_t Segments = 120, SDL_FColor Color = {255.f,255.f,255.f,255.f})
	{
		TMatrix TransformMatrix = TMatrix::TransformToMatrix(PivotTransform);
		std::vector<SDL_Vertex> Verts = {Segments,SDL_Vertex()};
		float AngleStep = static_cast<float>(360.f / Segments);

		for (int i = 0; i < Segments; i++)
		{
			float CurrentAngle = (AngleStep * i * (std::numbers::pi_v<float> / 180.f));
		
			Verts[i].color = Color;
			Verts[i].position.x = Radius * cos(CurrentAngle);
			Verts[i].position.y = Radius * sin(CurrentAngle);
		}
		
		Triangulate(Verts, Color);

		//Apply PivotTransform
		for (auto& Vert : Verts)
		{
			Vert.position = TransformMatrix * Vert.position;
		}

		return Verts;
	}

	static void Triangulate(std::vector<SDL_Vertex>& Verts, const SDL_FColor& Color)
	{
		std::vector<SDL_Vertex> VBuffer = Verts;
		const size_t Segments = Verts.size();
		const size_t TriangleNum = Segments * 3;
		Verts.resize(TriangleNum);

		for (int i = 0; i < Segments; i++)
		{
			Verts[i * 3] = SDL_Vertex();
			Verts[i * 3].color = Color;
			Verts[i * 3 + 1] = VBuffer[i];
			Verts[i * 3 + 2] = VBuffer[(i + 1) % Segments];
		}
	}
};

class Rectangle
{
public:

	static std::vector<SDL_Vertex> Make(float Width, float Height, const Transform& PivotTransform = Transform(),SDL_FColor Color = { 255.f,255.f,255.f,255.f })
	{
		TMatrix TransformMatrix = TMatrix::TransformToMatrix(PivotTransform);
		std::vector<SDL_Vertex> Verts = {4, SDL_Vertex() };

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

		Triangulate(Verts);

		//Apply PivotTransform
		for (auto& Vert : Verts)
		{
			Vert.position = TransformMatrix * Vert.position;
		}

		return Verts;
	}

	static void Triangulate(std::vector<SDL_Vertex>& Verts)
	{
		std::vector<SDL_Vertex> VBuffer = Verts;
		const size_t TriangleNum = (Verts.size() - 2) * 3;
		Verts.resize(TriangleNum);

		Verts[0] = VBuffer[0];
		Verts[1] = VBuffer[1];
		Verts[2] = VBuffer[2];
		Verts[3] = VBuffer[3];
		Verts[4] = VBuffer[2];
		Verts[5] = VBuffer[1];
	}
};

class Avatar
{
public:

	static std::vector<SDL_Vertex> Make(float Radius = 25.f, float HeadWidth = 25.f, float HeadHeight = 15.f)
	{
		auto Verts = Circle::Make(Radius);
		auto RectVerts = Rectangle::Make(HeadHeight, HeadWidth, Transform({ 25.f,0.f },0.f,{1.f,1.f}));

		Verts.insert(Verts.begin(), RectVerts.begin(), RectVerts.end());

		return Verts;
	}
};