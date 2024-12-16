#pragma once
#include <vector>
#include <memory>
#include <random>
#include "WorldSubsystem.h"
#include "../GameObject/Controller/AIController.h"



class Game;

class AISystem : public WorldSubsystem
{
public:
	AISystem(World* InGameWorld);
	virtual void Initialize();
	virtual void Update(float DeltaTime);
	void SpawnRandomEnemy();

private:

	std::mt19937 RandomGenerator;
	std::vector<std::weak_ptr<AIController>> ActiveAIControllers;
};