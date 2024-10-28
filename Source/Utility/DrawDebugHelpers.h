#pragma once


struct SDL_Renderer;
struct Vector2;


class DrawDebugHelpers
{
public:
	static DrawDebugHelpers& Get() { return Instance; }


	void Initialize(SDL_Renderer* InRenderer);
	void DrawDebugCone(const Vector2& Origin, const Vector2& Direction, float Height, float Angle);


	
private:

	SDL_Renderer* Renderer = nullptr;
	static DrawDebugHelpers Instance;
};