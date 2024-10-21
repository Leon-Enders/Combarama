#include "RenderSystem.h"
#include "SDL3/SDL_render.h"
#include "../Render/RenderComponent.h"

RenderSystem RenderSystem::Instance;

void RenderSystem::Update()
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent->Update();
	}
}

void RenderSystem::Draw(SDL_Renderer* GameRenderer)
{
	for (auto& ActiveRenderComponent : RenderComponents)
	{
		ActiveRenderComponent->Draw(GameRenderer);
	}
}

void RenderSystem::AddRenderComponent(RenderComponent* RenderComponentToAdd)
{
	if (RenderComponentToAdd)
	{
		RenderComponents.push_back(RenderComponentToAdd);
	}
}

void RenderSystem::RemoveRenderComponent(RenderComponent* RenderComponentToRemove)
{
	auto Iterator = std::find(RenderComponents.begin(), RenderComponents.end(), RenderComponentToRemove);

	if (Iterator != RenderComponents.end())
	{
		RenderComponents.erase(Iterator);
	}
}
