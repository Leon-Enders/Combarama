#pragma once


class SDL_Renderer;
struct Vector2;


class DrawDebugHelpers
{

	static void DrawDebugCone(SDL_Renderer* Renderer, const Vector2& Origin, const Vector2& Direction, float Height, float Angle);

};