#include "RenderComponent.h"
#include "../Subsystem/RenderSystem.h"

RenderComponent::RenderComponent(const std::vector<SDL_Vertex>&& InTriangles, const Vector2& InPosition, float InRotation)
	:
	Triangles(InTriangles),
	Position(InPosition),
	Rotation(InRotation)
{
	RenderSystem::Get().AddRenderComponent(this);
}

RenderComponent::~RenderComponent()
{
	RenderSystem::Get().RemoveRenderComponent(this);
}

void RenderComponent::Draw(SDL_Renderer* GameRenderer)
{
	SDL_RenderGeometry(GameRenderer, NULL, Triangles.data(), static_cast<int>(Triangles.size()), NULL, 0);
}

void RenderComponent::UpdatePosition(const Vector2& NewPosition)
{
	float DeltaX = NewPosition.X - Position.X;
	float DeltaY = NewPosition.Y - Position.Y;

	Position.X = NewPosition.X;
	Position.Y = NewPosition.Y;

	for (auto& Vert : Triangles)
	{
		Vert.position.x += DeltaX;
		Vert.position.y += DeltaY;
	}
}

void RenderComponent::UpdateRotation(float DeltaRotation)
{
	float CosTheta = cos(DeltaRotation);
	float SinTheta = sin(DeltaRotation);

	for (auto& Vert : Triangles)
	{
		float RelativeX = Vert.position.x - Position.X;
		float RelativeY = Vert.position.y - Position.Y;

		float RotatedX = RelativeX * CosTheta - RelativeY * SinTheta;
		float RotatedY = RelativeX * SinTheta + RelativeY * CosTheta;

		Vert.position.x = RotatedX + Position.X;
		Vert.position.y = RotatedY + Position.Y;
	}
}

void RenderComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		Triangles[i].color = NewColor;
	}
}
