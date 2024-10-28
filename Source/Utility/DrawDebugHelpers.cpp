#include "DrawDebugHelpers.h"
#include <vector>
#include "SDL3/SDL_render.h"
#include "../Math/ComboramaMath.h"

DrawDebugHelpers DrawDebugHelpers::Instance;

void DrawDebugHelpers::Initialize(SDL_Renderer* InRenderer)
{
    Renderer = InRenderer;
}

void DrawDebugHelpers::DrawDebugCone(const Vector2& Origin, const Vector2& Direction, float Height, float Angle)
{
    int Anglesteps = 8;
    SDL_FPoint ConeOrigin = { Origin.X, Origin.Y };
    std::vector<SDL_FPoint> ConePoints;

    float Anglestep = Angle / Anglesteps; 

   
    ConePoints.push_back(ConeOrigin);

   
    for (int i = -Anglesteps / 2; i <= Anglesteps / 2; i++) {
        float currentAngle = Anglestep * i; 

       
        float rotatedX = Direction.X * cos(currentAngle) - Direction.Y * sin(currentAngle);
        float rotatedY = Direction.X * sin(currentAngle) + Direction.Y * cos(currentAngle);

       
        float pointX = ConeOrigin.x + rotatedX * Height;
        float pointY = ConeOrigin.y + rotatedY * Height;

      
        ConePoints.push_back({ pointX, pointY });
    }

    ConePoints.push_back(ConeOrigin);
    SDL_RenderLines(Renderer, ConePoints.data(), ConePoints.size());
}