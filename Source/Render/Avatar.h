#pragma once
#include "SDL3/SDL_render.h"
#include <vector>

struct Transform;
class RenderComponent;
//Helper class generating Vertices for an Avatar shape
struct Avatar
{
	Avatar()=default;

	static void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor, RenderComponent* InRenderComponent);
	static void GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& OriginTransform);
	
	static constexpr float Radius = 25.f;
	static constexpr float HeadWidth = 25.f;
	static constexpr float HeadHeight = 15.f;
};