#include "PrimitiveComponent.h"
#include "../../../Core/CoreMinimal.h"
#include "../GameObject/Actor.h"
#include "../World/World.h"



PrimitiveComponent::PrimitiveComponent(Actor* Owner, std::vector<SDL_Vertex> Triangles)
	:
	SceneComponent(Owner),
	Triangles(std::move(Triangles)),
	BodyProxy(this)
{
	BodyProxy.SetCollisionShape(CollisionShape::MakeCircle(10.f));
}

PrimitiveComponent::~PrimitiveComponent()
{
	GetWorld()->GetRenderScene().UnRegisterPrimitiveComponent(this);
	GetWorld()->GetPhysicsScene().UnRegisterBodyInstance(&BodyProxy);
	
}

void PrimitiveComponent::Initialize()
{

	GetWorld()->GetRenderScene().RegisterPrimitiveComponent(this);
	GetWorld()->GetPhysicsScene().RegisterBodyInstance(&BodyProxy);
}


void PrimitiveComponent::SetColor(SDL_FColor NewColor, int Offset)
{
	for (int i = Offset; i < Triangles.size(); i++)
	{
		Triangles[i].color = NewColor;
	}
}

void PrimitiveComponent::SetCollisionShape(const CollisionShape& Shape)
{
	BodyProxy.SetCollisionShape(Shape);
}

const CollisionShape& PrimitiveComponent::GetCollisionShape() const
{
	return BodyProxy.GetCollisionShape();
}

Drawable PrimitiveComponent::GetDrawable() const
{
	Drawable d = Drawable(Triangles);
	d.ApplyTransformation(GetWorldMatrix());

	return d;
}

DebugDrawable PrimitiveComponent::GetDebugDrawable() const
{
	DebugDrawable d = DebugDrawable(BodyProxy.GetDebugShape());
	d.ApplyTransformation(GetWorldMatrix());

	return d;
}



