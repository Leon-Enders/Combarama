#include "BodyInstance.h"
#include "../RenderCore/Misc/DebugPrimitiveFactory.h"
#include "../RenderCore/Misc/ColorHelper.h"

BodyInstance::BodyInstance(CollisionShape Shape, ECollisionResponseType CollisionResponse)
	:
	Shape(Shape),
	CollisionResponse(CollisionResponse)
{
	DebugShape = DebugCircle::Make(Shape.Radius, 120);
}
