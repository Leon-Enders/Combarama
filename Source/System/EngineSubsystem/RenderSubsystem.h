#pragma once
#include "EngineSubsystem.h"
#include "../../Render/CoordinateTransformer.h"
#include "../../Render/Camera.h"
#include "../../Render/Drawable.h"
#include <vector>

class PrimitiveComponent;

class RenderSubsystem : public EngineSubsystem
{
public:
	RenderSubsystem(SDL_Renderer* Renderer);

	void AddPrimitiveComponent(PrimitiveComponent& PrimitiveComponentToAdd);
	void RemovePrimitiveComponent(PrimitiveComponent& PrimitiveComponentToRemove);

	void Draw();
	Camera& GetCam() { return cam; };
private:
	CoordinateTransformer ct;
	Camera cam;
	std::vector<std::reference_wrapper<PrimitiveComponent>> PrimitiveComponents;
};