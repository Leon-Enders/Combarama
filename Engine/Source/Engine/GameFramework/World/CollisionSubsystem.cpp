#include "CollisionSubsystem.h"
#include <vector>
#include "../Scene/PhysicsScene.h"
#include "../GameObject/Actor.h"
#include "../Component/PrimitiveComponent.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/CollisionShape.h"
#include "../../../PhysicsCore/BodyInstance.h"

CollisionSubsystem::CollisionSubsystem(World* GameWorld)
	:
	WorldSubsystem(GameWorld)
{
}

void CollisionSubsystem::Initialize()
{
}

bool CollisionSubsystem::SweepByChannel(const PhysicsScene& PScene,
	const Vector2& StartLocation, 
	const Vector2& EndLocation, 
	CollisionResult& OutCollisionResult, 
	const CollisionShape& Shape, 
	ECollisionChannel CollisionChannel, 
	Actor* ActorToIgnore)const
{
	//TODO: Handle CollisionQuery
	// Iterate through the scene and check if the distance of the sweep is less than the distance to a bodyproxy
	// this results in a list of valid targets
	// sweep the shape against each valid target
	// Read how about how you would sweep?
	//First iteration only for circles


	std::vector<BodyInstance*> PotentialTargets;
	auto ShapeVariant = Shape.GetShapeVariant();

	if (const auto* CircleShape = std::get_if<CollisionShape::Circle>(&ShapeVariant))
	{
		// Calcuate the maximum Distance
		Vector2 DeltaLocationSE = StartLocation - EndLocation;
		float PotentialRadius = DeltaLocationSE.Size()+ CircleShape->Radius;

		for (const auto& OtherBody : PScene.GetBodyProxies())
		{
			const PrimitiveComponent* OtherPrimitiveComponent = OtherBody->GetOwningPrimitiveComponent();
			if (OtherPrimitiveComponent->GetOwner() == ActorToIgnore) continue;

			auto OtherShapeVariant = OtherBody->GetCollisionShape().GetShapeVariant();
			if (const auto* OtherCircleShape = std::get_if<CollisionShape::Circle>(&OtherShapeVariant))
			{
				Vector2 OtherLocation = OtherPrimitiveComponent->GetWorldTransform().Position;
				Vector2 DeltaLocationSO = OtherLocation - StartLocation;
				float DistanceShapeToComponent = DeltaLocationSO.Size();

				if (DistanceShapeToComponent < PotentialRadius + OtherCircleShape->Radius)
				{
					PotentialTargets.push_back(OtherBody);
				}
			}
		}
	}




	


	return false;
}
