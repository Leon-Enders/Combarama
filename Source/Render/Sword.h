#pragma once
#include <memory>
#include "RenderComponent.h"
#include "SDL3/SDL_render.h"




class Sword
{
public:
	Sword(const Vector2& InPosition , float Rotation);


private:

    SDL_Vertex SwordTriangles[15] =
    {
        {  118.f, 200.f },
        { 118.f, 100.f },
        { 132.f, 100.f },

        { 118.f, 200.f },
        { 132.f, 100.f },
        { 132.f, 200.f },

        { 100.f, 180.f},
        { 100.f, 170.f},
        { 150.f, 170.f },

        { 100.f, 180.f},
        { 150.f, 170.f },
        { 150.f, 180.f },

        { 115.f, 100.f },
        { 135.f, 100.f },
        { 125.f, 75.f}
    };
	std::unique_ptr<RenderComponent> SwordRenderComponent;
};