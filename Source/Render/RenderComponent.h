#pragma once
#include "../Math/Vector2.h"
#include "SDL3/SDL_render.h"
#include <vector>

struct SDL_Renderer;

class RenderComponent
{
public:
	RenderComponent(const std::vector<SDL_Vertex>&& InTriangles, const Vector2& InPosition, float InRotation, const Vector2& InOffset=Vector2(0.f,0.f));
	~RenderComponent();
	void Draw(SDL_Renderer* GameRenderer);

	void UpdatePosition(const Vector2& NewPosition);
	void UpdateRotation(float DeltaRotation);

	void SetColor(SDL_FColor NewColor, int Offset=0);
private:
	Vector2 Position = {0.f,0.f};
	float Rotation = 0.f;

	std::vector<SDL_Vertex> Triangles;
};