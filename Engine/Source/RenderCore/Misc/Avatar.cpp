#include "Avatar.h"
#include "../Component/PrimitiveComponent.h"
#include "../PrimitiveFactory/PrimitiveHelpers.h"
#include "../Math/Transform.h"


void Avatar::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor, PrimitiveComponent* InPrimitiveComponent)
{
	InPrimitiveComponent->SetColor(BodyColor);
	InPrimitiveComponent->SetColor(HeadColor, Circle::GetNumberOfVerts());
}

void Avatar::GenerateVertices(std::vector<SDL_Vertex>& OutVerts, const Transform& OriginTransform)
{

	Circle ACircle = Circle(Radius);
	ACircle.GetVerts(OutVerts);

	// LocalTransform for the head
	Transform LocalTransform;
	LocalTransform.Position = { 25.f,0.f };

	Rectangle ARect = Rectangle(HeadHeight, HeadWidth, LocalTransform);

	ARect.GetVerts(OutVerts);
}
