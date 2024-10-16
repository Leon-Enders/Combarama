#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

struct App
{
    SDL_Renderer* Renderer;
    SDL_Window* Window;
};