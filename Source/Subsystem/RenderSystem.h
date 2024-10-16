#pragma once
#include <vector>

class RenderComponent;
class SDL_Renderer;

class RenderSystem
{
public:
	RenderSystem(SDL_Renderer* InGameRenderer);

	void Update(float DeltaTime);


private:
	SDL_Renderer* GameRenderer = nullptr;

	std::vector<RenderComponent*> RenderComponents;
};