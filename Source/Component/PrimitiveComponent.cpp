#include "PrimitiveComponent.h"
#include "../System/RenderSystem.h"
#include "../Math/Matrix.h"

PrimitiveComponent::~PrimitiveComponent()
{
	//RenderSystem::Get().RemoveRenderComponent(*this);
}

void PrimitiveComponent::Initialize(Actor* Owner)
{
	ActorComponent::Initialize(Owner);

	
	//RenderSystem::Get().AddRenderComponent(*this);
	//TODO: Check how to handle the world transform + the local transform of this component
	RenderTriangles.resize(Triangles.size());
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(ComponentTransform);


	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].position = TransformMatrix * Triangles[i].position;
		RenderTriangles[i].color = Triangles[i].color;
	}
}

void PrimitiveComponent::Update(float DeltaTime)
{
	Matrix3x3 WorldTransformMatrix = Matrix3x3::Transform(GetWorldTransform());
	//TODO: Check how to handle the world transform + the local transform of this component

	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].position = WorldTransformMatrix * Triangles[i].position;
	}
}

void PrimitiveComponent::SetVerts(const std::vector<SDL_Vertex>&& InTriangles)
{
	Triangles = InTriangles;
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
