#pragma once
#include <vector>
#include "SDL3/SDL_pixels.h"

struct Transform;
struct SDL_Vertex;
class PrimitiveComponent;
//Helper class generating Vertices for an Avatar shape
struct Avatar
{
	Avatar()=default;

	static void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor, PrimitiveComponent* InPrimitiveComponent);
	static void GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& OriginTransform);
	static const float GetRadius(){ return Radius; }

	static constexpr float Radius = 25.f;
	static constexpr float HeadWidth = 25.f;
	static constexpr float HeadHeight = 15.f;
};