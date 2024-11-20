#include "PrimitiveComponent.h"
#include "../System/RenderSystem.h"


PrimitiveComponent::~PrimitiveComponent()
{
	RenderSystem::Get().RemoveRenderComponent(*this);
}

void PrimitiveComponent::Initialize(Actor* Owner)
{
	SceneComponent::Initialize(Owner);

	
	RenderSystem::Get().AddRenderComponent(*this);
}


void PrimitiveComponent::SetVerts(const std::vector<SDL_Vertex>&& InTriangles)
{
	Triangles = InTriangles;
	RenderTriangles.resize(Triangles.size());

	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].color = Triangles[i].color;
	}
}

void PrimitiveComponent::LateUpdate(float DeltaTime)
{
	ActorComponent::LateUpdate(DeltaTime);

	//Apply transform to verts to render from the world transform this component is attached to
	Matrix3x3 WorldTransformMatrix = Matrix3x3::Transform(GetWorldTransform());
	Matrix3x3 TransformMatrix = WorldTransformMatrix * LocalTransformMatrix;


	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].position = TransformMatrix * Triangles[i].position;
	}
}


void PrimitiveComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		RenderTriangles[i].color = NewColor;
	}
}

void PrimitiveComponent::Draw(SDL_Renderer* GameRenderer) const
{
	if (!IsRenderActive) return;
	SDL_RenderGeometry(GameRenderer, NULL, RenderTriangles.data(), static_cast<int>(RenderTriangles.size()), NULL, 0);
}

