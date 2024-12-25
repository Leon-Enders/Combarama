#include "PhysicsScene.h"
#include "../../../PhysicsCore/BodyInstance.h"
#include <algorithm>

void PhysicsScene::RegisterBodyInstance(BodyInstance* BodyInstanceProxy)
{
	BodyProxies.push_back(BodyInstanceProxy);
}

void PhysicsScene::UnRegisterBodyInstance(BodyInstance* BodyInstanceProxy)
{
	if (BodyProxies.size() == 0) return;
	std::erase_if(BodyProxies, [&](BodyInstance* BodyInstance)
		{
			return BodyInstance == BodyInstanceProxy;
		});
}

const std::vector<BodyInstance*>& PhysicsScene::GetBodyProxies() const
{
	return BodyProxies;
}
