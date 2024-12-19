#include "BodyInstance.h"
#include "../RenderCore/Misc/DebugPrimitiveFactory.h"
#include "../RenderCore/Misc/ColorHelper.h"

BodyInstance::BodyInstance(PrimitiveComponent* Owner, CollisionShape Shape = {})
	:
    Owner(Owner),
	Shape(Shape)
{
    //Set DebugShape
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

    //Initialize ResponsesForChannels
    ResponseForChannel.insert({ ECollisionChannel::ECC_None, ECollisionResponseType::ECR_Ignore });
    ResponseForChannel.insert({ ECollisionChannel::ECC_Visibility, ECollisionResponseType::ECR_Ignore });
    ResponseForChannel.insert({ ECollisionChannel::ECC_Projectile, ECollisionResponseType::ECR_Ignore });
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

void BodyInstance::SetCollisionResponseForChannel(ECollisionChannel CollisionChannel, ECollisionResponseType NewCollisionResponse)
{
    ResponseForChannel[CollisionChannel] = NewCollisionResponse;
}

const ECollisionResponseType& BodyInstance::GetCollisionResponseForChannel(const ECollisionChannel& CollisionChannel) const
{
    return ResponseForChannel.at(CollisionChannel);
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
