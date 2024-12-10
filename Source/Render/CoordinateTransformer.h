#pragma once
#include <vector>
#include "../CombaramaConstants.h"
#include "SDL3/SDL_render.h"


class CoordinateTransformer
{
public:
	
	void Draw(std::vector<SDL_Vertex> Model, SDL_Renderer* GameRenderer)const;

private:

	static constexpr float ViewportHalfWidth = Combarama::ViewportWidth / 2;
	static constexpr float ViewportHalfHeight = Combarama::ViewportHeight / 2;
};