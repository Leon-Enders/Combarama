#include "Avatar.h"

Avatar::Avatar(const Vector2& InPosition)
	:
	Position(InPosition)
{
	// Create Circle as visual representation for actor
	SDL_Vertex CircleCenter;
	CircleCenter.position.x = Position.X;
	CircleCenter.position.y = Position.Y;
	SDL_FColor BodyColor = { 0.f,0.2f,1.f, 1.f };

	Circle ACircle = Circle(Radius, CircleCenter, BodyColor);
	ACircle.InitializeCircle(Triangles);



	// Create a Rectangle as visual representation for the direction the actor is looking
	SDL_Vertex RectCenter;
	RectCenter.position.x = Position.X;
	RectCenter.position.y = Position.Y - 25.f;
	SDL_FColor HeadColor = { 0.f, 0.3f,0.6f,1.f };

	Rectangle ARect = Rectangle(RectCenter, HeadWidth, HeadHeight, HeadColor);
	ARect.InitializeRectangle(Triangles, Circle::GetVertNumber());

}
void Avatar::Draw(SDL_Renderer* Renderer)
{
	SDL_RenderGeometry(Renderer, NULL, Triangles, MaxVerts, NULL, 0);
}
