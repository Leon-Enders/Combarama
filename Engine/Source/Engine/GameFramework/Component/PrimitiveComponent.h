#pragma once
#include "SDL3/SDL_render.h"
#include "SceneComponent.h"
#include "../../../RenderCore/Drawable.h"
#include "../../../PhysicsCore/BodyInstance.h"


class PrimitiveComponent : public SceneComponent
{
public:
	PrimitiveComponent(Actor* Owner, std::vector<SDL_Vertex> Triangles);
	virtual ~PrimitiveComponent();
	virtual void Initialize() override;

	Drawable GetDrawable()const;
	Drawable GetDebugDrawable()const;

	void SetColor(SDL_FColor NewColor, int Offset = 0);
	const bool GetRenderActive()const { return IsRenderActive; }
	const bool GetDebugActive()const { return IsDebugActive; }

	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }
	void SetDebugActive(bool DebugActive) { IsDebugActive = DebugActive; }
private:
	//Collision
	BodyInstance BodyProxy;

	//Render
	bool IsRenderActive = true;
	bool IsDebugActive = true;
	std::vector<SDL_Vertex> Triangles;
};