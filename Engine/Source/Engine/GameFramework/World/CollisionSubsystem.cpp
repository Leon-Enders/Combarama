#include "CollisionSubsystem.h"
#include <vector>
#include "../Scene/PhysicsScene.h"
#include "../GameObject/Actor.h"
#include "../Component/PrimitiveComponent.h"
#include "../../../PhysicsCore/CollisionResult.h"
#include "../../../PhysicsCore/CollisionShape.h"
#include "../../../PhysicsCore/BodyInstance.h"
#include "../../../Core/Math/ComboramaMath.h"
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
	const ECollisionChannel& CollisionChannel, 
	Actor* ActorToIgnore)const
{
	//First iteration only for circles
	bool HasCollided = false;

	std::vector<BodyInstance*> PotentialTargets;
	auto ShapeVariant = Shape.GetShapeVariant();

	if (const auto* CircleShape = std::get_if<CollisionShape::Circle>(&ShapeVariant))
	{
		// Calcuate the maximum Distance
		Vector2 DeltaLocationSE = EndLocation-StartLocation;
		float PotentialRadius = DeltaLocationSE.Size()+ CircleShape->Radius;

		for (const auto& OtherBody : PScene.GetBodyProxies())
		{
			// Skip this body if it ignores the current CollisionChannel
			if (OtherBody->GetCollisionResponseForChannel(CollisionChannel) == ECollisionResponseType::ECR_Ignore) continue;

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
			if (const auto* OtherRectShape = std::get_if<CollisionShape::Rect>(&OtherShapeVariant))
			{
				Vector2 OtherLocation = OtherPrimitiveComponent->GetWorldTransform().Position;
				Vector2 DeltaLocationSO = OtherLocation - StartLocation;
				float DistanceShapeToComponent = DeltaLocationSO.Size();
				float BoundingCircleRadius = Vector2(OtherRectShape->HalfExtentX, OtherRectShape->HalfExtentY).Size();


				if (DistanceShapeToComponent < PotentialRadius + BoundingCircleRadius)
				{
					PotentialTargets.push_back(OtherBody);
				}
			}
		}

		Vector2 DirectionToEnd = DeltaLocationSE.GetNormalized();
		int MaxSweepSteps = static_cast<int>(PotentialRadius / (CircleShape->Radius / 2.f));

		for (const auto& OtherBody : PotentialTargets)
		{
			const PrimitiveComponent* OtherPrimitiveComponent = OtherBody->GetOwningPrimitiveComponent();
			auto OtherShapeVariant = OtherBody->GetCollisionShape().GetShapeVariant();

			for (int i = 0; i <= MaxSweepSteps; i++)
			{
				Vector2 OtherLocation = OtherPrimitiveComponent->GetWorldTransform().Position;
				Vector2 SweptLocation = StartLocation + DirectionToEnd * static_cast<float>(i);

				
				if (const auto* OtherCircleShape = std::get_if<CollisionShape::Circle>(&OtherShapeVariant))
				{
					//TODO: Is this correct order?
					Vector2 DeltaLocationSO = OtherLocation - SweptLocation;
					float DistanceShapeToComponent = DeltaLocationSO.Size();
					float RadiusSum = CircleShape->Radius + OtherCircleShape->Radius;

					if (DistanceShapeToComponent < RadiusSum)
					{
						Vector2 DirectionToOtherOrigin = StartLocation.DirectionToTarget(OtherLocation);
						Vector2 ImpactPoint = OtherLocation - (DirectionToOtherOrigin * (RadiusSum + 1));

						//Handle Hit or Overlap
						switch (OtherBody->GetCollisionResponseForChannel(CollisionChannel))
						{
						case ECollisionResponseType::ECR_Overlap:
							HasCollided = true;
							//Handle Queue OverlapEvent
							break;
						case ECollisionResponseType::ECR_Block:
							OutCollisionResult.ImpactPoint = ImpactPoint;
							OutCollisionResult.Position = OtherLocation;
							OutCollisionResult.bBlockingHit = true;
							HasCollided = true;
							//TODO: Queue CollisionEvents
							break;
						default:
							break;
						}
					}
				}
			

				if (const auto* OtherBoxShape = std::get_if<CollisionShape::Rect>(&OtherShapeVariant))
				{
					Transform OtherWorldTransform = OtherPrimitiveComponent->GetWorldTransform();

					// Rotate the swept location to align with the rectangles local space
					float CosTheta = std::cos(-OtherWorldTransform.Rotation); // Rotation in local space
					float SinTheta = std::sin(-OtherWorldTransform.Rotation);

					float RotatedCX = CosTheta * (SweptLocation.X - OtherLocation.X) -
						SinTheta * (SweptLocation.Y - OtherLocation.Y);
					float RotatedCY = SinTheta * (SweptLocation.X - OtherLocation.X) +
						CosTheta * (SweptLocation.Y - OtherLocation.Y);

					// Find the closest point on the rectangle in local space
					float ClosestX = std::max(-OtherBoxShape->HalfExtentX, std::min(RotatedCX, OtherBoxShape->HalfExtentX));
					float ClosestY = std::max(-OtherBoxShape->HalfExtentY, std::min(RotatedCY, OtherBoxShape->HalfExtentY));

					// Calculate the squared distance between the rotated circle center and the closest point
					float DistanceSquared = std::pow(RotatedCX - ClosestX, 2) + std::pow(RotatedCY - ClosestY, 2);

					// Check if the circle is colliding with the rectangle
					if (DistanceSquared < std::pow(CircleShape->Radius, 2)) // Use squared radius for efficiency
					{
						// Calculate the direction from the circle center to the closest point
						Vector2 ClosestPoint(ClosestX, ClosestY);
						Vector2 RotatedCircleCenter(RotatedCX, RotatedCY);
						Vector2 DirectionToOtherPoint = (ClosestPoint - RotatedCircleCenter).Normalize(); // Ensure it's a unit vector

						// Calculate the impact point on the circle's boundary
						Vector2 ImpactPoint = ClosestPoint - (DirectionToOtherPoint * CircleShape->Radius);

						// Transform the impact point back to world space
						float CosWorldTheta = std::cos(OtherWorldTransform.Rotation); // Use positive rotation for world space
						float SinWorldTheta = std::sin(OtherWorldTransform.Rotation);

						float WorldImpactX = CosWorldTheta * ImpactPoint.X - SinWorldTheta * ImpactPoint.Y + OtherLocation.X;
						float WorldImpactY = SinWorldTheta * ImpactPoint.X + CosWorldTheta * ImpactPoint.Y + OtherLocation.Y;

						Vector2 WorldImpactPoint(WorldImpactX, WorldImpactY);

						Vector2 DirectionToImpactPoint = SweptLocation.DirectionToTarget(WorldImpactPoint);
						WorldImpactPoint += DirectionToImpactPoint * 1.1f;

						// Handle the collision or overlap event
						switch (OtherBody->GetCollisionResponseForChannel(CollisionChannel))
						{
						case ECollisionResponseType::ECR_Overlap:
							HasCollided = true;
							// TODO: Handle queue overlap event
							break;

						case ECollisionResponseType::ECR_Block:
							OutCollisionResult.ImpactPoint = WorldImpactPoint;
							OutCollisionResult.Position = OtherLocation;
							OutCollisionResult.bBlockingHit = true;
							HasCollided = true;
							// TODO: Queue collision events
							break;

						default:
							break;
						}
					}
				}
			}

		}
	}

	return HasCollided;
}
