#include "BoundingBox.h"
#include "SDL3/SDL_log.h"
#include "../Math/Matrix.h"

BoundingBox::BoundingBox(const Vector2 InOrigin, float InBoxHalfWidth, float InBoxHalfHeight)
	:
	Origin(InOrigin),
	BoxHalfWidth(InBoxHalfWidth),
	BoxHalfHeight(InBoxHalfHeight)
{
	BoundingBoxPoints.resize(4);
	BoundingBoxPointsLocal.resize(4);

	BoundingBoxPoints[0].X = - BoxHalfWidth;  // Top-left corner
	BoundingBoxPoints[0].Y = - BoxHalfHeight;

	BoundingBoxPoints[1].X = + BoxHalfWidth;  // Top-right corner
	BoundingBoxPoints[1].Y = - BoxHalfHeight;

	BoundingBoxPoints[2].X = + BoxHalfWidth;  // Bottom-right corner
	BoundingBoxPoints[2].Y = + BoxHalfHeight;

	BoundingBoxPoints[3].X = - BoxHalfWidth;  // Bottom-left corner
	BoundingBoxPoints[3].Y = + BoxHalfHeight;

	BoundingBoxPointsLocal = BoundingBoxPoints;
}

void BoundingBox::Update(const Transform& NewTransform)
{
	Matrix3x3 TransformMatrix = Matrix3x3::Transform(NewTransform);

	for (int i = 0; i < 4; i++)
	{
		BoundingBoxPoints[i] = TransformMatrix.MultiplyVector2(BoundingBoxPointsLocal[i]);
	}
}


bool BoundingBox::IsCollidingWith(const BoundingBox& Other, float& overlapX, float& overlapY) const
{
    
    const auto& cornersA = BoundingBoxPoints;
    const auto& cornersB = Other.GetBoundingBoxPoints();

    // List of all potential separating axes (4 edges, 2 from each box)
    std::vector<Vector2> axes;

    // Add the edge normals of this bounding box
    for (int i = 0; i < 4; ++i)
    {
        Vector2 edge = cornersA[(i + 1) % 4] - cornersA[i];
        axes.push_back(edge.Perpendicular().Normalize()); // Get the normal axis
    }

    // Add the edge normals of the other bounding box
    for (int i = 0; i < 4; ++i)
    {
        Vector2 edge = cornersB[(i + 1) % 4] - cornersB[i];
        axes.push_back(edge.Perpendicular().Normalize());
    }

    // Initialize overlaps as a large value
    overlapX = std::numeric_limits<float>::max();
    overlapY = std::numeric_limits<float>::max();
    Vector2 minOverlapAxis;

    // Check for separation on each axis
    for (const auto& axis : axes)
    {
        float minA, maxA;
        ProjectOntoAxis(cornersA, axis, minA, maxA);

        float minB, maxB;
        ProjectOntoAxis(cornersB, axis, minB, maxB);

        // Check for gap
        if (maxA < minB || maxB < minA)
        {
            return false; // No collision if there’s a separating axis
        }

        // Calculate overlaps
        float overlap = std::min(maxA - minB, maxB - minA);
        if (axis == axes[0] || axis == axes[1]) // Assuming X axes are the first two
        {
            overlapX = std::min(overlapX, overlap);
        }
        else // Y axes are the next two
        {
            overlapY = std::min(overlapY, overlap);
        }
    }

    return true;
}

void BoundingBox::ProjectOntoAxis(const std::vector<Vector2>& corners, const Vector2& axis, float& min, float& max) const
{
	// Initialize min and max projections
	min = max = corners[0].Dot(axis);

	// Project each corner onto the axis and find min and max
	for (const auto& corner : corners)
	{
		float projection = corner.Dot(axis);
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}
}
