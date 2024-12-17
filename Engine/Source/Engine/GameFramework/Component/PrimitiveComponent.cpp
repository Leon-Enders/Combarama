#include "PrimitiveComponent.h"
#include "../../../Core/CoreMinimal.h"
#include "../../Game.h"
#include "../GameObject/Actor.h"
#include "../World/World.h"
#include "../../../RenderCore/Drawable.h"



PrimitiveComponent::PrimitiveComponent(Actor* Owner, std::vector<SDL_Vertex> Triangles)
	:
	SceneComponent(Owner),
	Triangles(std::move(Triangles))
{
}

PrimitiveComponent::~PrimitiveComponent()
{
	AGame->GetRenderSubsystem()->RemovePrimitiveComponent(*this);
	//Register BodyInstance with PhsyicsScene
}

void PrimitiveComponent::Initialize()
{
	AGame->GetRenderSubsystem()->AddPrimitiveComponent(*this);
	//UnRegister BodyInstance with PhsyicsScene
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

	//TODO: use component transform in worldspace, currently it takes the roottransform of the owning actor
	
	d.ApplyTransformation(GetWorldMatrix());

	return d;
}



