#pragma once
#include "../EngineSubsystem.h"
#include "../../RenderCore/CoordinateTransformer.h"
#include "../../RenderCore/Drawable.h"
#include <vector>

class PrimitiveComponent;
class CameraComponent;

class RenderSubsystem : public EngineSubsystem
{
public:
	RenderSubsystem(SDL_Renderer* Renderer);

	void SetActiveCamera(CameraComponent* ActiveCam);
	void AddPrimitiveComponent(PrimitiveComponent& PrimitiveComponentToAdd);
	void RemovePrimitiveComponent(PrimitiveComponent& PrimitiveComponentToRemove);

	void Draw();

	CoordinateTransformer& GetCoordinateTransformer() { return ct; };
private:
	CoordinateTransformer ct;
	CameraComponent* ActiveCamera = nullptr;
	std::vector<std::reference_wrapper<PrimitiveComponent>> PrimitiveComponents;
};