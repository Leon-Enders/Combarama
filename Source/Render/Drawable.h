#pragma once
#include <vector>
#include "SDL3/SDL_render.h"


class Drawable
{
public:

	Drawable(const std::vector<SDL_Vertex>& Model)
		:
		Model(&Model)
	{}

	void Translate(const Vector2& translation_in)
	{
		transform.Position += translation_in;
	}
	void Scale(float Scalar)
	{
		transform.Scale *= Scalar;
		transform.Position *= Scalar;
	}
	void Scale(const Vector2& Scale)
	{
		transform.Scale.X *= Scale.X;
		transform.Scale.Y *= Scale.Y;
		transform.Position.X *= Scale.X;
		transform.Position.Y *= Scale.Y;
	}

	void Render(SDL_Renderer* Renderer)
	{
		std::vector<SDL_Vertex> CModel = *Model;

		for (auto& v : CModel)
		{
			v.position.x *= transform.Scale.X;
			v.position.y *= transform.Scale.Y;
			v.position.x += transform.Position.X;
			v.position.y += transform.Position.Y;
		}


		SDL_RenderGeometry(Renderer, NULL, CModel.data(), static_cast<int>(CModel.size()), NULL, 0);
	}

private:
	Transform transform;
	const std::vector<SDL_Vertex>* Model;
};