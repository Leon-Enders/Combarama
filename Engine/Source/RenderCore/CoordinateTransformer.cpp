#include "CoordinateTransformer.h"
#include "../Core/Math/Transform.h"
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

	InDrawable.ApplyTransformation(
		TMatrix::Translate(ViewportCenter) *
		TMatrix::FlipY()
	);

	InDrawable.Render(Renderer);
}
