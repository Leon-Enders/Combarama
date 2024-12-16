#pragma once
#include <vector>
#include "../Core/Misc/CombaramaConstants.h"

class Drawable;
struct SDL_Renderer;

class CoordinateTransformer
{
public:
	CoordinateTransformer(SDL_Renderer* Renderer);
	void Draw(Drawable& InDrawable)const;

private:

	SDL_Renderer* Renderer;

	static constexpr float ViewportHalfWidth = Combarama::ViewportWidth / 2;
	static constexpr float ViewportHalfHeight = Combarama::ViewportHeight / 2;
};