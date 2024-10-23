#pragma once
#include "../Math/Transform.h"
#include "SDL3/SDL_render.h"
#include <vector>
#include <functional>

class Actor;

class RenderComponent
{
public:
	RenderComponent(const std::vector<SDL_Vertex>&& InTriangles, const Actor& InOwningActor);
	~RenderComponent();

	void Update();
	void Draw(SDL_Renderer* GameRenderer)const;
	
	void SetColor(SDL_FColor NewColor, int Offset=0);
	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }

private:

	Transform RenderTransform;
	std::reference_wrapper<const Actor> OwningActor;
	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
	std::vector<SDL_Vertex> RenderTriangles;
};