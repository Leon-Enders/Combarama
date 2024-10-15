#pragma once
#include "SDL3/SDL_render.h"
#include "vector"
#include "PrimitiveHelpers.h"
#include "Vector2.h"

class Avatar
{
public:
	Avatar(const Vector2& InPosition);

	void UpdatePosition(const Vector2& NewPosition);
	void UpdateRotation(float DeltaRotation);
	
	void Draw(SDL_Renderer* Renderer);

private:
	
	Vector2 Position;
	static constexpr float Radius = 25.f;
	static constexpr float HeadWidth = 25.f;
	static constexpr float HeadHeight = 15.f;
	static constexpr int MaxVerts = Circle::GetVertNumber() + Rectangle::GetVertNumber();

	SDL_Vertex Triangles[MaxVerts];
	int TrianglesSize = 0;
};