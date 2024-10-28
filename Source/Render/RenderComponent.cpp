#include "RenderComponent.h"
#include "../System/RenderSystem.h"
#include "../Entity/Actor.h"
#include "../Math/Matrix.h"

RenderComponent::RenderComponent(const Actor& InOwningActor, const std::vector<SDL_Vertex>&& InTriangles)
	:
	Triangles(InTriangles),
	OwningActor(std::ref(InOwningActor))
{
	Initialize();

	RenderSystem::Get().AddRenderComponent(*this);
}

RenderComponent::~RenderComponent()
{
	RenderSystem::Get().RemoveRenderComponent(*this);
}

void RenderComponent::Draw(SDL_Renderer* GameRenderer)const
{
	if (!IsRenderActive) return;
	SDL_RenderGeometry(GameRenderer, NULL, RenderTriangles.data(), static_cast<int>(Triangles.size()), NULL, 0);
}

void RenderComponent::Initialize()
{
	RenderTriangles.resize(Triangles.size());
	RenderTransform = OwningActor.get().GetTransform();

	Matrix3x3 TransformMatrix = Matrix3x3::Transform(RenderTransform);
		

	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].position = TransformMatrix * Triangles[i].position;
		RenderTriangles[i].color = Triangles[i].color;
	}

}

void RenderComponent::Update()
{
	if (RenderTransform == OwningActor.get().GetTransform())
	{
		return;
	}
	RenderTransform = OwningActor.get().GetTransform();
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(RenderTransform);
	
	
	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		RenderTriangles[i].position = TransformMatrix * Triangles[i].position;
	}
}

void RenderComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		RenderTriangles[i].color = NewColor;
	}
}
