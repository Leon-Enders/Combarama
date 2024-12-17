#pragma once
#include <vector>
#include <memory>
#include <random>
#include "WorldSubsystem.h"
#include "../GameObject/Controller/AIController.h"


class AISubsystem : public WorldSubsystem
{
public:
	AISubsystem(World* GameWorld);
	virtual void Initialize();
	void SpawnRandomEnemy();

private:

	std::mt19937 RandomGenerator;
	std::vector<std::weak_ptr<AIController>> ActiveAIControllers;
};