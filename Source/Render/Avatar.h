#pragma once
#include "SDL3/SDL_render.h"
#include "vector"
#include "../Utility/PrimitiveHelpers.h"
#include "../Math/Vector2.h"

class Avatar
{
public:
	Avatar(const Vector2& InPosition, SDL_FColor BodyColor = { 0.f,0.2f,1.f, 1.f }, SDL_FColor HeadColor = { 0.f, 0.3f,0.6f,1.f });

	void UpdatePosition(const Vector2& NewPosition);
	void UpdateRotation(float DeltaRotation);
	void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor);
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