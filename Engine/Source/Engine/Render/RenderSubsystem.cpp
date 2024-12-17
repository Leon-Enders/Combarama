#include "RenderSubsystem.h"
#include "../GameFramework/Component/PrimitiveComponent.h"
#include "../GameFramework/Component/CameraComponent.h"
#include "../GameFramework/Scene/RenderScene.h"

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

void RenderSubsystem::Draw(const RenderScene& RScene)
{
	if (!ActiveCamera) return;

	for (const auto& p : RScene.GetPrimitiveComponents())
	{
		if (!p->GetRenderActive()) continue;
		ActiveCamera->Draw(p->GetDrawable());
		if (p->GetDebugActive())
		{
			ActiveCamera->Draw(p->GetDebugDrawable());
		}
	}
}
