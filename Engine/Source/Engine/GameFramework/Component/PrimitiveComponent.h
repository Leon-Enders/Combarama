#pragma once
#include "SDL3/SDL_render.h"
#include "SceneComponent.h"
#include "../../../RenderCore/Drawable.h"
#include "../../../RenderCore/DebugDrawable.h"
#include "../../../PhysicsCore/BodyInstance.h"


class PrimitiveComponent : public SceneComponent
{
public:
	PrimitiveComponent(Actor* Owner, std::vector<SDL_Vertex> Triangles);
	virtual ~PrimitiveComponent();
	virtual void Initialize() override;

	/*Render*/
	Drawable GetDrawable()const;
	DebugDrawable GetDebugDrawable()const;
	const bool GetRenderActive()const { return IsRenderActive; }
	const bool GetDebugActive()const { return IsDebugActive; }

	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }
	void SetDebugActive(bool DebugActive) { IsDebugActive = DebugActive; }
	void SetColor(SDL_FColor NewColor, int Offset = 0);

	/*Collision*/
	void SetCollisionShape(const CollisionShape& Shape);
	void SetCollisionResponseForChannel(ECollisionChannel CollisionChannel, ECollisionResponseType NewCollisionResponse);
	const CollisionShape& GetCollisionShape()const;
	
private:
	/*Render*/
	bool IsRenderActive = true;
	bool IsDebugActive = true;
	std::vector<SDL_Vertex> Triangles;

	/*Collision*/
	BodyInstance BodyProxy;
};