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
	Transform WorldTransform = GetWorldTransform();
	InDrawable.ApplyTransformation(
		TMatrix::Scale(WorldTransform.Scale.X) *
		TMatrix::Translate(WorldTransform.Position *-1.f)
	);

	CT.Draw(InDrawable);
}

void CameraComponent::Draw(DebugDrawable InDrawable) const
{
	Transform WorldTransform = GetWorldTransform();
	InDrawable.ApplyTransformation(
		TMatrix::Scale(WorldTransform.Scale.X) *
		TMatrix::Translate(WorldTransform.Position * -1.f)
	);

	CT.Draw(InDrawable);
}
