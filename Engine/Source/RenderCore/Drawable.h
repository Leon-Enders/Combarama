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

	void Render(SDL_Renderer* Renderer)
	{
		std::vector<SDL_Vertex> CModel = *Model;

		for (auto& v : CModel)
		{
			v.position = Transformation * v.position;
		}

		SDL_RenderGeometry(Renderer, NULL, CModel.data(), static_cast<int>(CModel.size()), NULL, 0);
	}

private:
	TMatrix Transformation = TMatrix::Identity();
	const std::vector<SDL_Vertex>* Model;
};