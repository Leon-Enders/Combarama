#pragma once
#include <variant>
#include "SDL3/SDL_rect.h"
#include "../Core/Math/Vector2.h"

struct CollisionShape
{
	struct Rect
	{
		float HalfExtentX;
		float HalfExtentY;
	};

	struct Circle
	{
		float Radius;
	}´;

	struct Line
	{
		SDL_FPoint P1;
		SDL_FPoint P2;
	};

	using ShapeVariant = std::variant<Line,Rect,Circle>;
	ShapeVariant Shape;

	auto GetShape()
	{
		return Shape;
	}

	static CollisionShape MakeRect(const Vector2& RectHalfExtent)
	{
		CollisionShape RectShape;
		RectShape.Shape = Rect{ RectHalfExtent.X ,RectHalfExtent.Y };
		return RectShape;
	}

	/** Static utility function to make a sphere */
	static CollisionShape MakeCircle(const float CircleRadius)
	{
		CollisionShape CircleShape;
		CircleShape.Shape = Circle{ CircleRadius };
		return CircleShape;
	}
	
	static CollisionShape MakeLine(const SDL_FPoint P1, const SDL_FPoint P2)
	{
		CollisionShape LineShape;
		LineShape.Shape = Line{ P1, P2 };
		return LineShape;
	}
};
