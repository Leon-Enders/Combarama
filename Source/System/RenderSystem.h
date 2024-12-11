#pragma once
#include <vector>
#include <functional>

class PrimitiveComponent;
struct SDL_Renderer;

class RenderSystem
{
public:
	static RenderSystem& Get() { return Instance; }

	void Draw()const;

	void AddRenderComponent(PrimitiveComponent& PrimitiveComponentToAdd);
	void RemoveRenderComponent(PrimitiveComponent& PrimitiveComponentToRemove);

private:
	RenderSystem() = default;
	static RenderSystem Instance;
	std::vector<std::reference_wrapper<PrimitiveComponent>> PrimitiveComponents;
};