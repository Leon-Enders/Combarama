#include "Avatar.h"
#include <vector>
#include "../Utility/PrimitiveHelpers.h"

Avatar::Avatar(const Vector2& InPosition, float Rotation)
{
	std::vector<SDL_Vertex> AvatarVerts;

	SDL_Vertex CircleCenter;
	CircleCenter.position.x = InPosition.X;
	CircleCenter.position.y = InPosition.Y;

	Circle ACircle = Circle(Radius, CircleCenter);
	ACircle.GetVerts(AvatarVerts);


	SDL_Vertex RectCenter;
	RectCenter.position.x = InPosition.X;
	RectCenter.position.y = InPosition.Y - 25.f;

	Rectangle ARect = Rectangle(RectCenter, HeadWidth, HeadHeight);

	ARect.GetVerts(AvatarVerts);

	AvatarRenderComponent = std::make_unique<RenderComponent>(std::move(AvatarVerts), InPosition, Rotation);
}

void Avatar::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor)
{
	AvatarRenderComponent->SetColor(BodyColor);
	AvatarRenderComponent->SetColor(HeadColor, Circle::GetNumberOfVerts());
}