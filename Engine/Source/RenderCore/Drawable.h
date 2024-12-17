#pragma once
#include <vector>
#include "SDL3/SDL_render.h"
#include "../Core/Math/Transform.h"
#include "../Core/Math/Matrix.h"

class Drawable
{
public:

	Drawable(const std::vector<SDL_Vertex>& Model)
		:
		Model(&Model)
	{}


	void ApplyTransformation(const TMatrix& InTransformation)
	{
		Transformation = InTransformation * Transformation;
	}

	void SetAsLine(bool AsLine) { RenderAsLine = AsLine; }

	void Render(SDL_Renderer* Renderer)
	{
		std::vector<SDL_Vertex> CModel = *Model;

		for (auto& v : CModel)
		{
			v.position = Transformation * v.position;
		}

		if (!RenderAsLine)
		{
			SDL_RenderGeometry(Renderer, NULL, CModel.data(), static_cast<int>(CModel.size()), NULL, 0);
			return;
		}
		
		std::vector<SDL_FPoint> ModelPoints;

		for (auto& v : CModel)
		{
			ModelPoints.push_back(v.position);
		}

		SDL_RenderLines(Renderer, ModelPoints.data(), static_cast<int>(ModelPoints.size()));
	}

private:
	TMatrix Transformation = TMatrix::Identity();
	const std::vector<SDL_Vertex>* Model;
	//const std::vector<SDL_FPoint>* DebugShape;
	bool RenderAsLine = false;
};