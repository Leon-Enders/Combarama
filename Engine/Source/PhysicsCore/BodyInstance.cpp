#include "BodyInstance.h"
#include "../RenderCore/Misc/DebugPrimitiveFactory.h"
#include "../RenderCore/Misc/ColorHelper.h"

BodyInstance::BodyInstance(PrimitiveComponent* Owner, CollisionShape Shape, ECollisionResponseType CollisionResponse)
	:
    Owner(Owner),
	Shape(Shape),
	CollisionResponse(CollisionResponse)
{
    const auto& ShapeVariant = Shape.GetShapeVariant();

    //Default to Circle DebugShape
    DebugShape = DebugCircle::Make(10.f);

    if (const auto* LineShape = std::get_if<CollisionShape::Line>(&ShapeVariant))
    {
        DebugShape = std::vector<SDL_FPoint>{ LineShape->P1, LineShape->P2};
    }
    else if (const auto* RectShape = std::get_if<CollisionShape::Rect>(&ShapeVariant))
    {
        DebugShape = DebugRect::Make(RectShape->HalfExtentX, RectShape->HalfExtentY);
    }
    else if (const auto* CircleShape = std::get_if<CollisionShape::Circle>(&ShapeVariant))
    {
        DebugShape = DebugCircle::Make(CircleShape->Radius);
    }
}
void BodyInstance::SetCollisionShape(const CollisionShape& ShapeToSet)
{
    Shape = ShapeToSet;

    const auto& ShapeVariant = Shape.GetShapeVariant();

    if (const auto* LineShape = std::get_if<CollisionShape::Line>(&ShapeVariant))
    {
        DebugShape = std::vector<SDL_FPoint>{ LineShape->P1, LineShape->P2 };
    }
    if (const auto* RectShape = std::get_if<CollisionShape::Rect>(&ShapeVariant))
    {
        DebugShape = DebugRect::Make(RectShape->HalfExtentX, RectShape->HalfExtentY);
    }
    if (const auto* CircleShape = std::get_if<CollisionShape::Circle>(&ShapeVariant))
    {
        DebugShape = DebugCircle::Make(CircleShape->Radius);
    }
}

const std::vector<SDL_FPoint>& BodyInstance::GetDebugShape()const
{
    return DebugShape;
}

const CollisionShape& BodyInstance::GetCollisionShape() const
{
    return Shape;
}

const PrimitiveComponent* BodyInstance::GetOwningPrimitiveComponent() const
{
    return Owner;
}
