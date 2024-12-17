#pragma once
#include <vector>

class BodyInstance;

class PhysicsScene
{
public:
	void RegisterBodyInstance(BodyInstance* BodyInstanceProxy);
	void RemoveBodyInstance(BodyInstance* BodyInstanceProxy);

private:
	std::vector<BodyInstance*> BodyProxies;
};