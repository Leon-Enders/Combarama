#pragma once
#include <vector>

class RenderComponent;
struct SDL_Renderer;

class RenderSystem
{
public:
	static RenderSystem& Get() { return Instance; }

	void Update(float DeltaTime);
	void Draw(SDL_Renderer* GameRenderer);

	void AddRenderComponent(RenderComponent* RenderComponentToAdd);
	void RemoveRenderComponent(RenderComponent* RenderComponentToRemove);

private:
	RenderSystem() = default;
	static RenderSystem Instance;
	std::vector<RenderComponent*> RenderComponents;
};