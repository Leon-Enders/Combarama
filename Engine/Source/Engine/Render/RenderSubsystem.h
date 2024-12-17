#pragma once
#include "../EngineSubsystem.h"
#include "../../RenderCore/CoordinateTransformer.h"
#include "../../RenderCore/Drawable.h"
#include <vector>

//TODO: RenderSubsystem should hold no state of the Primitive Components
//-> Create RenderScene in World which holds state for the things to render
class CameraComponent;
class RenderScene;

class RenderSubsystem : public EngineSubsystem
{
public:
	RenderSubsystem(SDL_Renderer* Renderer);

	void SetActiveCamera(CameraComponent* ActiveCam);
	void Draw(const RenderScene& RScene);

	CoordinateTransformer& GetCoordinateTransformer() { return ct; };
private:
	CoordinateTransformer ct;
	CameraComponent* ActiveCamera = nullptr;
};