#include "PrimitiveComponent.h"
#include "../Entity/Actor.h"
#include "../World/World.h"
#include "../Render/Drawable.h"
#include "../Game.h"


PrimitiveComponent::~PrimitiveComponent()
{
	GetOwner()->GetWorld()->GetGame()->GetRenderSubsystem()->RemovePrimitiveComponent(*this);
}

void PrimitiveComponent::Initialize(Actor* Owner)
{
	SceneComponent::Initialize(Owner);

	GetOwner()->GetWorld()->GetGame()->GetRenderSubsystem()->AddPrimitiveComponent(*this);
}


void PrimitiveComponent::SetVerts(std::vector<SDL_Vertex> InTriangles)
{
	Triangles = std::move(InTriangles);

	for (size_t i = 0; i < Triangles.size(); ++i)
	{
		Triangles[i].position.x += GetWorldTransform().Position.X;
		Triangles[i].position.y += GetWorldTransform().Position.Y;
	}
}



void PrimitiveComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		Triangles[i].color = NewColor;
	}
}

Drawable PrimitiveComponent::GetDrawable() const
{
	Drawable d = Drawable(Triangles);

	d.Scale(GetScale());
	d.Translate(GetPosition());

	return d;
}



