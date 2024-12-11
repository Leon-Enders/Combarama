#include "CoordinateTransformer.h"
#include "../Math/Vector2.h"

void CoordinateTransformer::Draw(std::vector<SDL_Vertex> Model)const
{

	for (auto& v : Model)
	{
		v.position.y *= -1.f;

		v.position.x += ViewportHalfWidth;
		v.position.y += ViewportHalfHeight;
	}


	SDL_RenderGeometry(Renderer, NULL, Model.data(), static_cast<int>(Model.size()), NULL, 0);
}
