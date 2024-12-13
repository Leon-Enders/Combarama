#pragma once
#include <vector>
#include "SDL3/SDL_render.h"
#include "../../Core/Math/Transform.h"


class Sword
{
public:
	Sword()=default;

    static void GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& PivotTransform = {});
private:

    static constexpr SDL_Vertex SwordTriangles[15] =
    {
          { -7.0f, 62.5f }, 
          { -7.0f, -37.5f },
          {  7.0f, -37.5f },

          { -7.0f, 62.5f }, 
          {  7.0f, -37.5f },
          {  7.0f, 62.5f }, 

          { -25.0f, 42.5f },
          { -25.0f, 32.5f },
          {  25.0f, 32.5f },

          { -25.0f, 42.5f },
          {  25.0f, 32.5f },
          {  25.0f, 42.5f },

          { -10.0f, -37.5f },
          {  10.0f, -37.5f },
          {   0.0f, -62.5f }
    };
};