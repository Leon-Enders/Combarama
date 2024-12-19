#include "CollisionSubsystem.h"
#include <vector>
#include "../Scene/PhysicsScene.h"
#include "../GameObject/Actor.h"
#include "../Component/PrimitiveComponent.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/CollisionShape.h"
#include "../../../PhysicsCore/BodyInstance.h"
#include "SDL3/SDL_log.h"

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
		Vector2 DeltaLocationSE = EndLocation-StartLocation;
		float PotentialRadius = DeltaLocationSE.Size()+ CircleShape->Radius;

		for (const auto& OtherBody : PScene.GetBodyProxies())
		{
			const PrimitiveComponent* OtherPrimitiveComponent = OtherBody->GetOwningPrimitiveComponent();
			if (OtherPrimitiveComponent->GetOwner() == ActorToIgnore) continue;

			auto OtherShapeVariant = OtherBody->GetCollisionShape().GetShapeVariant();
			if (const auto* OtherCircleShape = std::get_if<CollisionShape::Circle>(&OtherShapeVariant))
			{
				//TODO: Create Helper method to check overlap for 2 circles
				Vector2 OtherLocation = OtherPrimitiveComponent->GetWorldTransform().Position;
				Vector2 DeltaLocationSO = OtherLocation - StartLocation;
				float DistanceShapeToComponent = DeltaLocationSO.Size();

				if (DistanceShapeToComponent < PotentialRadius + OtherCircleShape->Radius)
				{
					PotentialTargets.push_back(OtherBody);
				}
			}
		}

		//if (PotentialTargets.size() > 0)
		//{
		//	SDL_Log("PotentialTargets!");
		//}
		//else
		//{
		//	SDL_Log("NoPotentialTargets!");
		//}
		Vector2 DirectionToEnd = DeltaLocationSE.GetNormalized();
		int MaxSweepSteps = static_cast<int>(PotentialRadius / (CircleShape->Radius / 2.f));

		for (const auto& OtherBody : PotentialTargets)
		{
			const PrimitiveComponent* OtherPrimitiveComponent = OtherBody->GetOwningPrimitiveComponent();
			auto OtherShapeVariant = OtherBody->GetCollisionShape().GetShapeVariant();
			if (const auto* OtherCircleShape = std::get_if<CollisionShape::Circle>(&OtherShapeVariant))
			{
				for (int i = 0; i <= MaxSweepSteps; i++)
				{
					Vector2 OtherLocation = OtherPrimitiveComponent->GetWorldTransform().Position;
					Vector2 DirectionToOtherOrigin = StartLocation.DirectionToTarget(OtherLocation) * -1.f;

					Vector2 SweptLocation = StartLocation + DirectionToEnd * i;

					Vector2 DeltaLocationSO = OtherLocation - SweptLocation;
					float DistanceShapeToComponent = DeltaLocationSO.Size();
					float RadiusSum = CircleShape->Radius + OtherCircleShape->Radius;

					if (DistanceShapeToComponent < RadiusSum)
					{
						//This is our hit
						Vector2 ImpactPoint = OtherLocation - (DirectionToOtherOrigin * (RadiusSum+1));

						OutCollisionResult.ImpactPoint = ImpactPoint;
						OutCollisionResult.Position = OtherLocation;
						OutCollisionResult.bBlockingHit = true;
						
						return true;
					}
				}
			}
		}
	}

	return false;
}
