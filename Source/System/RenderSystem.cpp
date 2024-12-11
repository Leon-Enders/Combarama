#include "RenderSystem.h"
#include "SDL3/SDL_render.h"
#include "../Component/PrimitiveComponent.h"
#include "../Render/Camera.h"

RenderSystem RenderSystem::Instance;

void RenderSystem::Draw()const
{

	for (auto& Cam : Cameras)
	{
		for (auto& ActiveRenderComponent : PrimitiveComponents)
		{
			Cam.get().Draw(ActiveRenderComponent.get().GetModel());
		}
	}

	
}

void RenderSystem::AddCamera(Camera& CameraToAdd)
{
	Cameras.push_back(std::ref(CameraToAdd));
}

void RenderSystem::RemoveCamera(Camera& CameraToRemove)
{
	std::erase_if(Cameras, [&](std::reference_wrapper<Camera> Cam)
		{
			return &Cam.get() == &CameraToRemove;
		});
}

void RenderSystem::AddPrimitiveComponent(PrimitiveComponent& PrimitiveComponentToAdd)
{
	
	PrimitiveComponents.push_back(std::ref(PrimitiveComponentToAdd));
	
}

void RenderSystem::RemovePrimitiveComponent(PrimitiveComponent& PrimitiveComponentToRemove)
{
	std::erase_if(PrimitiveComponents, [&](std::reference_wrapper<PrimitiveComponent> Component)
		{
			return &Component.get() == &PrimitiveComponentToRemove;
		});
}
