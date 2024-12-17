#pragma once
#include <vector>

class PrimitiveComponent;

class RenderScene
{
public:
	void RegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister);
	void UnRegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister);

private:
	std::vector<PrimitiveComponent*> PrimitiveComponents;
};