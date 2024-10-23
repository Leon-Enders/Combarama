#include "RenderSystem.h"
#include "SDL3/SDL_render.h"
#include "../Render/RenderComponent.h"

RenderSystem RenderSystem::Instance;

void RenderSystem::Update()const
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent.get().Update();
	}
}

void RenderSystem::Draw(SDL_Renderer* GameRenderer)const
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent.get().Draw(GameRenderer);
	}
}

void RenderSystem::AddRenderComponent(RenderComponent& RenderComponentToAdd)
{
	
	RenderComponents.push_back(RenderComponentToAdd);
	
}

void RenderSystem::RemoveRenderComponent(RenderComponent& RenderComponentToRemove)
{
	std::erase_if(RenderComponents, [&](std::reference_wrapper<RenderComponent> Component)
		{
			return &Component.get() == &RenderComponentToRemove;
		});
}
