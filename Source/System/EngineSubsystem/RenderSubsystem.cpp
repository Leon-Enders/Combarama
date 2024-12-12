#include "RenderSubsystem.h"
#include <algorithm>
#include <iterator>
#include "../../Component/PrimitiveComponent.h"

RenderSubsystem::RenderSubsystem(SDL_Renderer* Renderer)
	:
	EngineSubsystem(),
	ct(Renderer),
	cam(ct)
{
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
	for (auto& p : PrimitiveComponents)
	{
		cam.Draw(p.get().GetDrawable());
	}
}
