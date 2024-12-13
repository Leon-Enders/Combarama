#include "CameraComponent.h"

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Draw(Drawable InDrawable) const
{
	InDrawable.Translate(ComponentTransform.Position * -1.f);
	InDrawable.Scale(ComponentTransform.Scale);
	WorldCoordinateTransformer.Draw(InDrawable);
}
