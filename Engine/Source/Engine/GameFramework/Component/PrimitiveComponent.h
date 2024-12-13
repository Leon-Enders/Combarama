#pragma once
#include "SDL3/SDL_render.h"
#include "SceneComponent.h"
#include "../../../RenderCore/Drawable.h"


class PrimitiveComponent : public SceneComponent
{
public:
	PrimitiveComponent(Actor* Owner, std::vector<SDL_Vertex> Triangles);
	virtual ~PrimitiveComponent();
	virtual void Initialize() override;

	void SetColor(SDL_FColor NewColor, int Offset = 0);
	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }

	Drawable GetDrawable()const;
private:

	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
};