#pragma once
#include "SDL3/SDL_render.h"
#include "SceneComponent.h"



class PrimitiveComponent : public SceneComponent
{
public:

	virtual ~PrimitiveComponent();
	virtual void Initialize(Actor* Owner) override;
	virtual void LateUpdate(float DeltaTime) override;

	void SetVerts(const std::vector<SDL_Vertex>&& InTriangles);
	void SetColor(SDL_FColor NewColor, int Offset = 0);
	void SetRenderActive(bool RenderActive) { IsRenderActive = RenderActive; }


	std::vector<SDL_Vertex> GetModel()const;
private:

	bool IsRenderActive = true;
	std::vector<SDL_Vertex> Triangles;
	std::vector<SDL_Vertex> RenderTriangles;

	Matrix3x3 RenderTransformMatrix;
};