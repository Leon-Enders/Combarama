#pragma once
#include <memory>
#include "RenderComponent.h"
#include "SDL3/SDL_render.h"




class Sword
{
public:
	Sword(const Transform& InTransform, const Vector2& SwordOffset);

    RenderComponent* GetRenderComponent() { return SwordRenderComponent.get(); }
private:

   

    SDL_Vertex SwordTriangles[15] =
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
	std::unique_ptr<RenderComponent> SwordRenderComponent;
};