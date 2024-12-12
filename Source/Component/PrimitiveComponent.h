#pragma once
#include "SDL3/SDL_render.h"
#include "SceneComponent.h"
#include "../Render/Drawable.h"


class PrimitiveComponent : public SceneComponent
{
public:

	virtual ~PrimitiveComponent();
	virtual void Initialize(Actor* Owner) override;

	void SetVerts(const std::vector<SDL_Vertex>&& InTriangles);
	void SetColor(SDL_FColor NewColor, int Offset = 0);
	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }

	Drawable GetDrawable()const;
private:

	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
};