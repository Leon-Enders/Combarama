#pragma once
#include <vector>

class BodyInstance;

class PhysicsScene
{
public:
	void RegisterBodyInstance(BodyInstance* BodyInstanceProxy);
	void UnRegisterBodyInstance(BodyInstance* BodyInstanceProxy);

	const std::vector<BodyInstance*>& GetBodyProxies()const;
private:
	std::vector<BodyInstance*> BodyProxies;
};