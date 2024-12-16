#include "RenderSubsystem.h"
#include <algorithm>
#include <ranges>
#include <iterator>
#include "../GameFramework/Component/PrimitiveComponent.h"
#include "../GameFramework/Component/CameraComponent.h"

RenderSubsystem::RenderSubsystem(SDL_Renderer* Renderer)
	:
	EngineSubsystem(),
	ct(Renderer)
{
}

void RenderSubsystem::SetActiveCamera(CameraComponent* ActiveCam)
{
	ActiveCamera = ActiveCam;
}

void RenderSubsystem::AddPrimitiveComponent(PrimitiveComponent& PrimitiveComponentToAdd)
{
	PrimitiveComponents.push_back(std::ref(PrimitiveComponentToAdd));
}

void RenderSubsystem::RemovePrimitiveComponent(PrimitiveComponent& PrimitiveComponentToRemove)
{
	if (PrimitiveComponents.size() == 0) return;

	std::erase_if(PrimitiveComponents, [&](std::reference_wrapper<PrimitiveComponent> Component)
		{
			return &Component.get() == &PrimitiveComponentToRemove;
		});
}

void RenderSubsystem::Draw()
{
	if (!ActiveCamera) return;

	for (const auto& p : PrimitiveComponents)
	{
		ActiveCamera->Draw(p.get().GetDrawable());
	}
}
