#pragma once
#include "../Math/Transform.h"
#include "SDL3/SDL_render.h"
#include <vector>

struct SDL_Renderer;

class RenderComponent
{
public:
	RenderComponent(const std::vector<SDL_Vertex>&& InTriangles, const Transform& InTransform);
	~RenderComponent();
	void Draw(SDL_Renderer* GameRenderer);


	void Update(float DeltaTime);
	void UpdatePosition(const Vector2& NewPosition);
	void UpdateRotation(float NewRotation);
	void Rotate(float DeltaRotation);
	void SetColor(SDL_FColor NewColor, int Offset=0);

	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }

private:
	Transform RenderTransform;
	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
};