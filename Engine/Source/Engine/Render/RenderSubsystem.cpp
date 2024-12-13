#include "RenderSubsystem.h"
#include <algorithm>
#include <iterator>
#include "../../Component/PrimitiveComponent.h"
#include "../../Component/CameraComponent.h"

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
