#include "RenderSystem.h"
#include "SDL3/SDL_render.h"
#include "../Render/RenderComponent.h"

RenderSystem::RenderSystem(SDL_Renderer* InGameRenderer)
	:
	GameRenderer(InGameRenderer)
{

}

void RenderSystem::Update(float DeltaTime)
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent->Draw(GameRenderer);
	}
}
