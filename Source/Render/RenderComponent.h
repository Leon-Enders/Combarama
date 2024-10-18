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


	void Update(float DeltaTime);
	void UpdatePosition(const Vector2& NewPosition);
	void UpdateRotation(float NewRotation);
	void Rotate(float DeltaRotation);
	void SetRotation(float NewRotation);
	void SetColor(SDL_FColor NewColor, int Offset=0);

	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }

private:
	Vector2 Position = {0.f,0.f};
	float Rotation = 0.f;
	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
};