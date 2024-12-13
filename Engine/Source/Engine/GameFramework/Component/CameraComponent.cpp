#include "CameraComponent.h"
#include "../../../Core/CoreMinimal.h"
#include "../../Game.h"

CameraComponent::CameraComponent(Actor* Owner)
	:
	SceneComponent(Owner),
	CT(AGame->GetRenderSubsystem()->GetCoordinateTransformer())
{
}

CameraComponent::~CameraComponent()
{
	AGame->GetRenderSubsystem()->SetActiveCamera(nullptr);
}

void CameraComponent::Initialize()
{
	AGame->GetRenderSubsystem()->SetActiveCamera(this);
}


void CameraComponent::Draw(Drawable InDrawable) const
{
	InDrawable.Translate(ComponentTransform.Position * -1.f);
	InDrawable.Scale(ComponentTransform.Scale);
	CT.Draw(InDrawable);
}
