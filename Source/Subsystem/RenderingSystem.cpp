#include "RenderingSystem.h"
#include "SDL3/SDL_render.h"
#include "../Render/RenderComponent.h"

RenderingSystem::RenderingSystem(SDL_Renderer* InGameRenderer)
	:
	GameRenderer(InGameRenderer)
{

}

void RenderingSystem::Update(float DeltaTime)
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent->Draw(GameRenderer);
	}
}
