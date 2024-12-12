#pragma once
#include "EngineSubsystem.h"

class SDL_Renderer;

class RenderSubsystem : public EngineSubsystem
{
public:
	RenderSubsystem(SDL_Renderer* Renderer);

	


private:
	SDL_Renderer* Renderer = nullptr;
};