#include "RenderScene.h"
#include <algorithm>
#include "../Component/PrimitiveComponent.h"


void RenderScene::RegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister)
{
	PrimitiveComponents.push_back(PrimitiveComponentToRegister);
}

void RenderScene::UnRegisterPrimitiveComponent(PrimitiveComponent* PrimitiveComponentToRegister)
{
	std::erase_if(PrimitiveComponents, [&](PrimitiveComponent* PrimitiveComp)
		{
			return PrimitiveComp == PrimitiveComponentToRegister;
		});
}

const std::vector<PrimitiveComponent*>& RenderScene::GetPrimitiveComponents() const
{
	return PrimitiveComponents;
}
