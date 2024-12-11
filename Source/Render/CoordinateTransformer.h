#pragma once
#include <vector>
#include "../CombaramaConstants.h"
#include "SDL3/SDL_render.h"


class CoordinateTransformer
{
public:
	CoordinateTransformer(SDL_Renderer* Renderer)
		:
		Renderer(Renderer)
	{}
	void Draw(std::vector<SDL_Vertex> Model)const;

private:

	SDL_Renderer* Renderer = nullptr;

	static constexpr float ViewportHalfWidth = Combarama::ViewportWidth / 2;
	static constexpr float ViewportHalfHeight = Combarama::ViewportHeight / 2;
};