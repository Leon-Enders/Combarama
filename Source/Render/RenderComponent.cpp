#include "RenderComponent.h"
#include "../System/RenderSystem.h"
#include "../Entity/Actor.h"
#include "../Math/Matrix.h"

RenderComponent::RenderComponent(const std::vector<SDL_Vertex>&& InTriangles,const Actor* InOwningActor)
	:
	Triangles(InTriangles),
	OwningActor(InOwningActor)
{

	TransformedTriangles.resize(Triangles.size());
	if (OwningActor)
	{
		// Cache the Initial Transform of the Actor who owns this Component
		RenderTransform = InOwningActor->GetTransform();
	}


	RenderSystem::Get().AddRenderComponent(this);
}

RenderComponent::~RenderComponent()
{
	RenderSystem::Get().RemoveRenderComponent(this);
}

void RenderComponent::Draw(SDL_Renderer* GameRenderer)
{
	if (!IsRenderActive) return;
	SDL_RenderGeometry(GameRenderer, NULL, TransformedTriangles.data(), static_cast<int>(Triangles.size()), NULL, 0);
}

void RenderComponent::Update()
{
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(OwningActor->GetTransform());
	
	
	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		TransformedTriangles[i].position = TransformMatrix * Triangles[i].position;
		TransformedTriangles[i].color = Triangles[i].color; 
	}
}

void RenderComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		Triangles[i].color = NewColor;
	}
}
