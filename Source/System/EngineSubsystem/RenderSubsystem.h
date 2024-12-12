#pragma once
#include "EngineSubsystem.h"
#include "../../Render/CoordinateTransformer.h"
#include "../../Render/Camera.h"
#include <vector>

class SDL_Renderer;

class RenderSubsystem : public EngineSubsystem
{
public:
	RenderSubsystem(SDL_Renderer* Renderer);

	
	void Draw();

private:



	CoordinateTransformer ct;
	Camera cam;
	//Active Camera Transform Matrix
};