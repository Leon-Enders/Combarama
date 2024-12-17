#pragma once
#include <vector>

class PrimitiveComponent;

class RenderScene
{
public:
	void RegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister);
	void UnRegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister);

	const std::vector<PrimitiveComponent*>& GetPrimitiveComponents()const;
private:
	std::vector<PrimitiveComponent*> PrimitiveComponents;
};