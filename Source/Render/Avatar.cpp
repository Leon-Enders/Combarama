#include "Avatar.h"
#include "RenderComponent.h"
#include "../Utility/PrimitiveHelpers.h"
#include "../Math/Transform.h"


void Avatar::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor, RenderComponent* InRenderComponent)
{
	InRenderComponent->SetColor(BodyColor);
	InRenderComponent->SetColor(HeadColor, Circle::GetNumberOfVerts());
}

void Avatar::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& OriginTransform)
{

	Circle ACircle = Circle(Radius);
	ACircle.GetVerts(OutVerts);

	// Offset In local Space
	Transform LocalTransform;
	LocalTransform.Position = { 0.f,-25.f };
	Rectangle ARect = Rectangle(HeadWidth, HeadHeight, LocalTransform);

	ARect.GetVerts(OutVerts);
}
