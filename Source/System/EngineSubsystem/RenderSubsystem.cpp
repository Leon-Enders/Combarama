#include "RenderSubsystem.h"

RenderSubsystem::RenderSubsystem(SDL_Renderer* Renderer)
	:
	EngineSubsystem(),
	ct(Renderer),
	cam(ct)
{
}

void RenderSubsystem::Draw()
{
	//cam.Draw()
}
