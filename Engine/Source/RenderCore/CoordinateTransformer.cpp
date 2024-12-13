#include "CoordinateTransformer.h"
#include "../Math/Transform.h"
#include "Drawable.h"
#include "SDL3/SDL_render.h"

CoordinateTransformer::CoordinateTransformer(SDL_Renderer* Renderer)
	:
	Renderer(Renderer)
{
}

void CoordinateTransformer::Draw(Drawable& InDrawable)const
{
	Vector2 ViewportCenter = Vector2(ViewportHalfWidth, ViewportHalfHeight);

	InDrawable.Scale(Vector2(1.f, -1.f));
	InDrawable.Translate(ViewportCenter);

	InDrawable.Render(Renderer);
}
