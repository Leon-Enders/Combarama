#pragma once
#include <vector>
#include <functional>

class PrimitiveComponent;
class Camera;

class RenderSystem
{
public:
	static RenderSystem& Get() { return Instance; }

	void Draw()const;

	void AddCamera(Camera& CameraToAdd);
	void RemoveCamera(Camera& CameraToRemove);

	void AddPrimitiveComponent(PrimitiveComponent& PrimitiveComponentToAdd);
	void RemovePrimitiveComponent(PrimitiveComponent& PrimitiveComponentToRemove);

private:
	RenderSystem() = default;
	static RenderSystem Instance;
	std::vector<std::reference_wrapper<PrimitiveComponent>> PrimitiveComponents;
	std::vector<std::reference_wrapper<Camera>> Cameras;
};