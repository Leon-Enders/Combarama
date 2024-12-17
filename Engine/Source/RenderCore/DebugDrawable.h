#pragma once
#include <vector>
#include "SDL3/SDL_render.h"
#include "../Core/Math/Transform.h"
#include "../Core/Math/Matrix.h"

class DebugDrawable
{
public:

	DebugDrawable(const std::vector<SDL_FPoint>& Shape)
		:
		Shape(&Shape)
	{}

	void ApplyTransformation(const TMatrix& InTransformation)
	{
		Transformation = InTransformation * Transformation;
	}

	void Render(SDL_Renderer* Renderer)
	{
		std::vector<SDL_FPoint> CShape = *Shape;

		for (auto& p : CShape)
		{
			p = Transformation * p;
		}
		SDL_SetRenderDrawColorFloat(Renderer, 255.f, 0.f, 0.f, 255.f);
		SDL_RenderLines(Renderer, CShape.data(), static_cast<int>(CShape.size()));
		SDL_RenderLine(Renderer, CShape.back().x, CShape.back().y, CShape.front().x, CShape.front().y);
	}

private:
	TMatrix Transformation = TMatrix::Identity();
	const std::vector<SDL_FPoint>* Shape;
};