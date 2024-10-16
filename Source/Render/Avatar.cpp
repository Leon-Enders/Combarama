#include "Avatar.h"

Avatar::Avatar(const Vector2& InPosition, SDL_FColor BodyColor, SDL_FColor HeadColor)
	:
	Position(InPosition)
{
	// Create Circle as visual representation for actor
	SDL_Vertex CircleCenter;
	CircleCenter.position.x = Position.X;
	CircleCenter.position.y = Position.Y;

	Circle ACircle = Circle(Radius, CircleCenter, BodyColor);
	ACircle.Initialize(Triangles);



	// Create a Rectangle as visual representation for the direction the actor is looking
	SDL_Vertex RectCenter;
	RectCenter.position.x = Position.X;
	RectCenter.position.y = Position.Y - 25.f;

	Rectangle ARect = Rectangle(RectCenter, HeadWidth, HeadHeight, HeadColor);
	ARect.Initialize(Triangles, Circle::GetVertNumber());

}
void Avatar::UpdatePosition(const Vector2& NewPosition)
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
void Avatar::UpdateRotation(float DeltaRotation)
{
	float CosTheta = cos(DeltaRotation);
	float SinTheta = sin(DeltaRotation);

	for (int i = 0; i < MaxVerts; ++i)
	{

		float RelativeX = Triangles[i].position.x - Position.X;
		float RelativeY = Triangles[i].position.y - Position.Y;


		float RotatedX = RelativeX * CosTheta - RelativeY * SinTheta;
		float RotatedY = RelativeX * SinTheta + RelativeY * CosTheta;


		Triangles[i].position.x = RotatedX + Position.X;
		Triangles[i].position.y = RotatedY + Position.Y;
	}
	
}
void Avatar::SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor)
{
	for (int i = 0; i < Circle::GetVertNumber(); ++i)
	{
		Triangles[i].color = BodyColor;
	}

	for (int i = Circle::GetVertNumber(); i < MaxVerts; i++)
	{
		Triangles[i].color = HeadColor;
	}
}
void Avatar::Draw(SDL_Renderer* Renderer)
{
	SDL_RenderGeometry(Renderer, NULL, Triangles, MaxVerts, NULL, 0);
}
