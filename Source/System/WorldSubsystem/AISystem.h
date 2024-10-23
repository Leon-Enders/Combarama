#pragma once
#include <vector>
#include <random>
#include <functional>
#include "WorldSubsystem.h"
#include "../../Entity/Enemy.h"
#include "../../Controller/AIController.h"



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
	std::vector<std::reference_wrapper<AIController>> ActiveAIControllers;
};