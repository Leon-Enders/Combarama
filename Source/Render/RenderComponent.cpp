#include "RenderComponent.h"
#include "../Subsystem/RenderSystem.h"

RenderComponent::RenderComponent(const std::vector<SDL_Vertex>&& InTriangles,const Transform& InTransform)
	:
	Triangles(InTriangles),
	RenderTransform(InTransform)
{
	RenderSystem::Get().AddRenderComponent(this);
}

RenderComponent::~RenderComponent()
{
	RenderSystem::Get().RemoveRenderComponent(this);
}

void RenderComponent::Draw(SDL_Renderer* GameRenderer)
{
	if (!IsRenderActive) return;
	SDL_RenderGeometry(GameRenderer, NULL, Triangles.data(), static_cast<int>(Triangles.size()), NULL, 0);
}

void RenderComponent::Update(float DeltaTime)
{

}

void RenderComponent::UpdatePosition(const Vector2& NewPosition)
{
	Vector2 DeltaPosition = NewPosition - RenderTransform.Position;

	RenderTransform.Position = NewPosition;

	for (auto& Vert : Triangles)
	{
		Vert.position.x += DeltaPosition.X;
		Vert.position.y += DeltaPosition.Y;
	}
}

void RenderComponent::UpdateRotation(float NewRotation)
{
	float DeltaRotation = RenderTransform.Rotation - NewRotation;

	Rotate(DeltaRotation);
	RenderTransform.Rotation = NewRotation;
}

void RenderComponent::Rotate(float DeltaRotation)
{
	float CosTheta = cos(DeltaRotation);
	float SinTheta = sin(DeltaRotation);


	for (auto& Vert : Triangles)
	{
		float RelativeX = Vert.position.x - RenderTransform.Position.X;
		float RelativeY = Vert.position.y - RenderTransform.Position.Y;

		float RotatedX = RelativeX * CosTheta - RelativeY * SinTheta;
		float RotatedY = RelativeX * SinTheta + RelativeY * CosTheta;

		Vert.position.x = RotatedX + RenderTransform.Position.X;
		Vert.position.y = RotatedY + RenderTransform.Position.Y;
	}
}

void RenderComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		Triangles[i].color = NewColor;
	}
}
