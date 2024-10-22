#pragma once
#include "SDL3/SDL_render.h"
#include "../Math/Transform.h"



struct CollisionHelper
{
public:
	CollisionHelper(SDL_Renderer* Renderer)
		:
		GameRenderer(Renderer)
	{

	}



	
	void DrawHitbox(const Transform& InTransform, SDL_FRect* RectToDraw)
	{
		SDL_FRect Collider = *RectToDraw;
		Collider.x = InTransform.Position.X - (Collider.w / 2.f);
		Collider.y = InTransform.Position.Y - (Collider.h / 2.f);

		SDL_RenderRect(GameRenderer, RectToDraw);
	}

private:
	SDL_Renderer* GameRenderer;
};

