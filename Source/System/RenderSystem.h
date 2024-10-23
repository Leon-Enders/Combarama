#pragma once
#include <vector>
#include <functional>

class RenderComponent;
struct SDL_Renderer;

class RenderSystem
{
public:
	static RenderSystem& Get() { return Instance; }

	void Update()const;
	void Draw(SDL_Renderer* GameRenderer)const;

	void AddRenderComponent(RenderComponent& RenderComponentToAdd);
	void RemoveRenderComponent(RenderComponent& RenderComponentToRemove);

private:
	RenderSystem() = default;
	static RenderSystem Instance;
	std::vector<std::reference_wrapper<RenderComponent>> RenderComponents;
};