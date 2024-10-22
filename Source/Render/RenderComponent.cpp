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
	Matrix3x3 translate = Matrix3x3::translation(OwningActor->GetPosition().X, OwningActor->GetPosition().Y);
	// Apply the model matrix to all vertices (translation only for now)
	
	
	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		// Apply the translation to the local vertex position
		SDL_FPoint TransformedPos = translate * Triangles[i].position;

		// Update the transformed vertex position
		TransformedTriangles[i].position = TransformedPos;
		TransformedTriangles[i].color = Triangles[i].color; // Copy the color if needed
	}
}

void RenderComponent::UpdatePosition()
{
	////Calculate Delta To current Owner Position
	//Vector2 DeltaPosition = OwningActor->GetPosition()- RenderTransform.Position;
	//
	////Update the RenderTransform
	//RenderTransform.Position = OwningActor->GetPosition();
	//
	//for (auto& Vert : Triangles)
	//{
	//	Vert.position.x += DeltaPosition.X;
	//	Vert.position.y += DeltaPosition.Y;
	//}
}

void RenderComponent::UpdateRotation()
{
	//Calculate DeltaRotation to current Owner Rotation
	float DeltaRotation = RenderTransform.Rotation - OwningActor->GetRotation();

	Rotate(DeltaRotation);

	//Update RenderTransform
	RenderTransform.Rotation = OwningActor->GetRotation();
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
