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
					Vector2 DeltaLocationSO = SweptLocation-OtherLocation;
					float ClampedX = ComboramaMath::Clamp(DeltaLocationSO.X, -OtherBoxShape->HalfExtentX, OtherBoxShape->HalfExtentX);
					float ClampedY = ComboramaMath::Clamp(DeltaLocationSO.Y, -OtherBoxShape->HalfExtentY, OtherBoxShape->HalfExtentY);

					Vector2 ClosestPoint = OtherLocation + Vector2(ClampedX, ClampedY);
					Vector2 DeltaLocationCirToPoint = ClosestPoint - SweptLocation;
					float Distance = DeltaLocationCirToPoint.Size();

					if (Distance < CircleShape->Radius)
					{
						Vector2 DirectionToOtherPoint = StartLocation.DirectionToTarget(ClosestPoint);
						Vector2 ImpactPoint = ClosestPoint - (DirectionToOtherPoint * (CircleShape->Radius + 1));

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

			}

		}
	}

	return HasCollided;
}
