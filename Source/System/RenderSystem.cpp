#include "RenderSystem.h"
#include "SDL3/SDL_render.h"
#include "../Component/PrimitiveComponent.h"

RenderSystem RenderSystem::Instance;

void RenderSystem::Draw()const
{
	for (auto& ActiveRenderComponent : PrimitiveComponents)
	{
		ActiveRenderComponent.get().Draw();
	}
}

void RenderSystem::AddRenderComponent(PrimitiveComponent& PrimitiveComponentToAdd)
{
	
	PrimitiveComponents.push_back(std::ref(PrimitiveComponentToAdd));
	
}

void RenderSystem::RemoveRenderComponent(PrimitiveComponent& PrimitiveComponentToRemove)
{
	std::erase_if(PrimitiveComponents, [&](std::reference_wrapper<PrimitiveComponent> Component)
		{
			return &Component.get() == &PrimitiveComponentToRemove;
		});
}
