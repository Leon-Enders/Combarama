#include "PhysicsScene.h"
#include "../../../PhysicsCore/BodyInstance.h"
#include <algorithm>

void PhysicsScene::RegisterBodyInstance(BodyInstance* BodyInstanceProxy)
{
	BodyProxies.push_back(BodyInstanceProxy);
}

void PhysicsScene::UnRegisterBodyInstance(BodyInstance* BodyInstanceProxy)
{
	std::erase_if(BodyProxies, [&](BodyInstance* BodyInstance)
		{
			return BodyInstance == BodyInstanceProxy;
		});
}
