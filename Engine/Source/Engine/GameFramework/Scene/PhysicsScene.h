#pragma once
#include <vector>

struct BodyInstance;

class PhysicsScene
{
public:
	void RegisterBodyInstance(BodyInstance* BodyInstanceProxy);
	void UnRegisterBodyInstance(BodyInstance* BodyInstanceProxy);

private:
	std::vector<BodyInstance*> BodyProxies;
};