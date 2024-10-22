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
	SDL_Vertex CircleCenter;
	CircleCenter.position.x = OriginTransform.Position.X;
	CircleCenter.position.y = OriginTransform.Position.Y;

	Circle ACircle = Circle(Radius);
	ACircle.GetVerts(OutVerts);


	SDL_Vertex RectCenter;
	RectCenter.position.x = OriginTransform.Position.X;
	RectCenter.position.y = OriginTransform.Position.Y - 25.f;

	Rectangle ARect = Rectangle(HeadWidth, HeadHeight);

	ARect.GetVerts(OutVerts);
}
