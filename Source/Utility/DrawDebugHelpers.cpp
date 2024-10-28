#include "DrawDebugHelpers.h"
#include <vector>
#include "SDL3/SDL_render.h"
#include "../Math/ComboramaMath.h"

void DrawDebugHelpers::DrawDebugCone(SDL_Renderer* Renderer, const Vector2& Origin, const Vector2& Direction, float Height, float Angle)
{
    int Anglesteps = 8;  // Number of steps to create points along the cone angle
    SDL_FPoint ConeOrigin = { Origin.X, Origin.Y };
    std::vector<SDL_FPoint> ConePoints;

  
    float Anglestep = Angle / Anglesteps;

    // Add the origin as the first point
    ConePoints.push_back(ConeOrigin);

    // Generate points along the cone angle
    for (float i = -Angle / 2; i <= Angle / 2; i += Anglestep) {
        // Convert the angle to radians for trigonometric calculations

        // Calculate the direction vector rotated by the angle step
        float pointX = Origin.X + (Direction.X * cos(angleRad) - Direction.Y * sin(angleRad)) * Height;
        float pointY = Origin.Y + (Direction.X * sin(angleRad) + Direction.Y * cos(angleRad)) * Height;

        // Add the calculated point to the vector
        ConePoints.push_back({ pointX, pointY });
    }

    // Render the lines between the points
    SDL_RenderDrawLinesF(Renderer, ConePoints.data(), ConePoints.size());
