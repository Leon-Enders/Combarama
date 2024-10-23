#pragma once
#include <vector>
#include "SDL3/SDL_render.h"
#include "../Math/Transform.h"


class Sword
{
public:
	Sword()=default;

    static void GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& LocalTransform = {});
private:

    static constexpr SDL_Vertex SwordTriangles[15] =
    {
        {  18.f, 100.f },
        { 18.f, 0.f },
        { 32.f, 0.f },

        { 18.f, 100.f },
        { 32.f, 0.f },
        { 32.f, 100.f },

        { 0.f, 80.f},
        { 0.f, 70.f},
        { 50.f, 70.f },

        { 0.f, 80.f},
        { 50.f, 70.f },
        { 50.f, 80.f },

        { 15.f, 0.f },
        { 35.f, 0.f },
        { 25.f, -25.f}
    };
};